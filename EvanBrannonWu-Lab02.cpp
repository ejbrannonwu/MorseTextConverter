//Evan Brannon-Wu
//CS 124   10/06/2021
//Lab 02 - Sort, Search
//The program utilizes two sorting algorithms that measures their
//time for both sorted and unsorted sets of data.
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std::chrono;

//Prototypes
void printLast(std::vector<std::string> z);
void printFirst(std::vector<std::string> z);
void bubble_sort(std::vector<std::string> &v, std::vector<std::string> &z);
void selection_sort(std::vector<std::string> &v, std::vector<std::string> &z);
int min_position(std::vector<std::string> v, int from, int to);
void swap(std::string &x, std::string &y);
std::string preProcess(std::string word);
void merge(std::vector<std::string> &v, std::vector<std::string> &z, int from, int mid, int to);
void merge_sort(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to);
void insertion_sort(std::vector<std::string> &v, std::vector<std::string> &z, int size);
int partition(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to);
void quicksort(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to);
int linear_search(std::vector<std::string> z, int size, std::string value);
int binary_search(std::vector<std::string> z, int from, int to, std::string value);
void timeCalculation(double average[], double file[]);
void dataEntry(std::string fileName, std::vector<std::string> &v, std::vector<std::string> &z);
void searches(std::vector<std::string> &v, std::vector<std::string> &z, std::string fileName, double times[], std::string target);
void printMenu(std::vector<std::string> z, char printChoice);
void sorts(std::string fileName, std::vector<std::string> &v, std::vector<std::string> &z, double times[]);
void timeTable(double timeA1[], double timeA2[]);

int main()
{
    char user;
    std::cout << "\nWelcome to the Sorting Algorithm Program."
              << "\nThis program takes in a multiple text files and cleans up their data."
              << "\nYou, as the user, can choose a combination of two of these files."
              << "\nFive sorting algorithms are used and their average times, over five runs, are reported."
              << "\nAs well as two searching algorithms with their average times."
              << "\nWould you like to try this program? Y or N: ";
    std::cin >> user;
    user = tolower(user);

    if (user != 'y' && user != 'n')
    {
        while (user != 'y' && user != 'n') //Acts as a default if neither 'y' or 'no' is chosen.
        {
            std::cout << "\nIncorrect Input. Please try again..."
                      << "\nWould you like to try this program? Y or N? ";
            std::cin >> user;
            user = tolower(user);
        }
    }

    while (user == 'y')
    {
        int choice;
        std::string target1, target2;
        char printChoice1, printChoice2;
        double timesFile1[70];
        double timesFile2[70];
        double timeAverage1[15];
        double timeAverage2[15];
        std::vector<std::string> setOfWordsLower;
        std::vector<std::string> setOfWordsPrint;
        std::string file1 = "Speeches.txt";
        std::string file2 = "HarryPotter.txt";
        std::string file3 = "Inception.txt";

        std::cout << "\nPlease choose the file combination: "
                  << "\n\t1) 5,000 words & 10,000 words"
                  << "\n\t2) 5,000 words & 20,000 words"
                  << "\n\t3) 10,000 words & 20,000 words"
                  << "\n\tChoice: ";
        std::cin >> choice;

        while (choice != 1 && choice != 2 && choice != 3)
        {
            std::cout << "\nInvalid Choice. Please choose again.";
            std::cout << "\n\nPlease choose the file combination: "
                      << "\n\t1) 5,000 words & 10,000 words"
                      << "\n\t2) 5,000 words & 20,000 words"
                      << "\n\t3) 10,000 words & 20,000 words"
                      << "\n\tChoice: ";
            std::cin >> choice;
        }
        if (choice == 1)
        {
            sorts(file1, setOfWordsLower, setOfWordsPrint, timesFile1);
            sorts(file2, setOfWordsLower, setOfWordsPrint, timesFile2);

            std::cout << "\n\nEnter word to search for in File One: ";
            std::cin >> target1;
            searches(setOfWordsLower, setOfWordsPrint, file1, timesFile1, target1);
            std::cout << "\n\nEnter word to search for in File Two: ";
            std::cin >> target2;
            searches(setOfWordsLower, setOfWordsPrint, file2, timesFile2, target2);

            dataEntry(file1, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file one? F or L? ";
            std::cin >> printChoice1;
            printChoice1 = tolower(printChoice1);
            printMenu(setOfWordsPrint, printChoice1);

            dataEntry(file2, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file two? F or L? ";
            std::cin >> printChoice2;
            printChoice2 = tolower(printChoice2);
            printMenu(setOfWordsPrint, printChoice2);

            timeCalculation(timeAverage1, timesFile1);
            timeCalculation(timeAverage2, timesFile2);

            timeTable(timeAverage1, timeAverage2);
        }
        if (choice == 2)
        {
            sorts(file1, setOfWordsLower, setOfWordsPrint, timesFile1);
            sorts(file3, setOfWordsLower, setOfWordsPrint, timesFile2);

            std::cout << "\n\nEnter word to search for in File One: ";
            std::cin >> target1;
            searches(setOfWordsLower, setOfWordsPrint, file1, timesFile1, target1);
            std::cout << "\n\nEnter word to search for in File Two: ";
            std::cin >> target2;
            searches(setOfWordsLower, setOfWordsPrint, file3, timesFile2, target2);

            dataEntry(file1, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file one? F or L? ";
            std::cin >> printChoice1;
            printChoice1 = tolower(printChoice1);
            printMenu(setOfWordsPrint, printChoice1);

            dataEntry(file3, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file two? F or L? ";
            std::cin >> printChoice2;
            printChoice2 = tolower(printChoice2);
            printMenu(setOfWordsPrint, printChoice2);

            timeCalculation(timeAverage1, timesFile1);
            timeCalculation(timeAverage2, timesFile2);

            timeTable(timeAverage1, timeAverage2);
        }
        if (choice == 3)
        {
            sorts(file2, setOfWordsLower, setOfWordsPrint, timesFile1);
            sorts(file3, setOfWordsLower, setOfWordsPrint, timesFile2);

            std::cout << "\n\nEnter word to search for in File One: ";
            std::cin >> target1;
            searches(setOfWordsLower, setOfWordsPrint, file2, timesFile1, target1);
            std::cout << "\n\nEnter word to search for in File Two: ";
            std::cin >> target2;
            searches(setOfWordsLower, setOfWordsPrint, file3, timesFile2, target2);

            dataEntry(file2, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file one? F or L? ";
            std::cin >> printChoice1;
            printChoice1 = tolower(printChoice1);
            printMenu(setOfWordsPrint, printChoice1);

            dataEntry(file3, setOfWordsLower, setOfWordsPrint);
            merge_sort(setOfWordsLower, setOfWordsPrint, 0, setOfWordsLower.size() - 1);
            std::cout << "\n\nWould you like to print the first or last 50 words for file two? F or L? ";
            std::cin >> printChoice2;
            printChoice2 = tolower(printChoice2);
            printMenu(setOfWordsPrint, printChoice2);

            timeCalculation(timeAverage1, timesFile1);
            timeCalculation(timeAverage2, timesFile2);

            timeTable(timeAverage1, timeAverage2);
        }
        std::cout << "\nWould you like to try again? Y or N? ";
        std::cin >> user;
        user = tolower(user);
    }

    if (user == 'n') //Exiting message if 'n' is chosen
    {
        std::cout << "\nThank you! Exiting Program....";
        return 0;
    }
}

void spaceCleaner(std::vector<std::string> &z)
{
    std::vector<std::string>::iterator it;
    it = z.begin();
    while (it != z.end())
    {
        if (*it == "")
        {
            z.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void timeTable(double timeA1[], double timeA2[])
{
    std::cout << std::endl
              << std::setw(35) << "File One Unsorted" << std::setw(25) << "File One Sorted" << std::setw(25) << "File Two Unsorted" << std::setw(25) << "File Two Sorted" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\nBubble Sort:" << std::setw(21) << timeA1[0] << std::setw(25) << timeA1[1] << std::setw(25) << timeA2[0] << std::setw(25) << timeA2[1] << std::endl
              << "Selection Sort:" << std::setw(18) << timeA1[2] << std::setw(25) << timeA1[3] << std::setw(25) << timeA2[2] << std::setw(25) << timeA2[3] << std::endl
              << "Insertion Sort:" << std::setw(18) << timeA1[4] << std::setw(25) << timeA1[5] << std::setw(25) << timeA2[4] << std::setw(25) << timeA2[5] << std::endl
              << "Merge Sort:" << std::setw(22) << timeA1[6] << std::setw(25) << timeA1[7] << std::setw(25) << timeA2[6] << std::setw(25) << timeA2[7] << std::endl
              << "Quick Sort:" << std::setw(22) << timeA1[8] << std::setw(25) << timeA1[9] << std::setw(25) << timeA2[8] << std::setw(25) << timeA2[9] << std::endl
              << "Linear Search:" << std::setw(19) << timeA1[10] << std::setw(50) << timeA2[10] << std::endl
              << "Binary Search:" << std::setw(44) << timeA1[11] << std::setw(50) << timeA2[11] << std::endl;
}

void sorts(std::string fileName, std::vector<std::string> &v, std::vector<std::string> &z, double times[])
{
    for (int i = 0; i < 5; i++) //File One Sorts
    {
        dataEntry(fileName, v, z);

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        bubble_sort(v, z); //Calls the bubblesort function which sorts unsorted array
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span11 = duration_cast<duration<double> >(t2 - t1);
        times[i] = time_span11.count();

        t1 = high_resolution_clock::now();
        bubble_sort(v, z); //Calls the bubblesort function which sorts sorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span12 = duration_cast<duration<double> >(t2 - t1);
        times[i + 5] = time_span12.count();
        v.clear(); //Clears vector to used again
        z.clear();

        dataEntry(fileName, v, z);

        t1 = high_resolution_clock::now();
        selection_sort(v, z); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span21 = duration_cast<duration<double> >(t2 - t1);
        times[i + 10] = time_span21.count();

        t1 = high_resolution_clock::now();
        selection_sort(v, z); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span22 = duration_cast<duration<double> >(t2 - t1);
        times[i + 15] = time_span22.count();
        v.clear(); //Clears vector to used again
        z.clear();

        dataEntry(fileName, v, z);

        t1 = high_resolution_clock::now();
        insertion_sort(v, z, v.size()); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span31 = duration_cast<duration<double> >(t2 - t1);
        times[i + 20] = time_span31.count();

        t1 = high_resolution_clock::now();
        insertion_sort(v, z, v.size()); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span32 = duration_cast<duration<double> >(t2 - t1);
        times[i + 25] = time_span32.count();
        v.clear(); //Clears vector to used again
        z.clear();

        dataEntry(fileName, v, z);

        t1 = high_resolution_clock::now();
        merge_sort(v, z, 0, v.size() - 1); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span41 = duration_cast<duration<double> >(t2 - t1);
        times[i + 30] = time_span41.count();

        t1 = high_resolution_clock::now();
        merge_sort(v, z, 0, v.size() - 1); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span42 = duration_cast<duration<double> >(t2 - t1);
        times[i + 35] = time_span42.count();
        v.clear(); //Clears vector to used again
        z.clear();

        dataEntry(fileName, v, z);

        t1 = high_resolution_clock::now();
        quicksort(v, z, 0, v.size() - 1); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span51 = duration_cast<duration<double> >(t2 - t1);
        times[i + 40] = time_span51.count();

        t1 = high_resolution_clock::now();
        quicksort(v, z, 0, v.size() - 1); //Calls the bubblesort function which sorts unsorted array
        t2 = high_resolution_clock::now();
        duration<double> time_span52 = duration_cast<duration<double> >(t2 - t1);
        times[i + 45] = time_span52.count();
        v.clear(); //Clears vector to used again
        z.clear();
    }
}

void printMenu(std::vector<std::string> z, char printChoice)
{
    while (printChoice != 'f' && printChoice != 'l')
    {
        std::cout << "\nError, that is not one of the options. Please try again? ";
        std::cin >> printChoice;
        printChoice = tolower(printChoice);
    }
    if (printChoice == 'f')
    {
        std::cout << std::endl;
        printFirst(z);
    }
    else if (printChoice == 'l')
    {
        std::cout << std::endl;
        printLast(z);
    }
}

void searches(std::vector<std::string> &v, std::vector<std::string> &z, std::string fileName, double times[], std::string target)
{
    int pos1, pos2;
    dataEntry(fileName, v, z);
    
    for (int i = 0; i < target.size(); i++)
    {
        target[i] = tolower(target[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        pos1 = linear_search(z, z.size(), target);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span1 = duration_cast<duration<double> >(t2 - t1);
        times[i + 50] = time_span1.count();
    }

    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    merge_sort(v, z, 0, z.size() - 1);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    duration<double> time_span3 = duration_cast<duration<double> >(t4 - t3);
    times[61] = time_span3.count(); //Sets the sort time to a later unused array index

    for (int i = 0; i < 5; i++)
    {
        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        pos2 = binary_search(z, 0, z.size() - 1, target);
        high_resolution_clock::time_point t6 = high_resolution_clock::now();
        duration<double> time_span2 = duration_cast<duration<double> >(t6 - t5);
        times[i + 55] = time_span2.count();
    }
    if (pos1 == -1)
    {
        std::cout << "Linear Search, " << target << " is not found in file." << std::endl;
    }
    else
    {
        std::cout << "Linear Search: Found in position " << pos1 << std::endl;
    }

    if (pos2 == -1)
    {
        std::cout << "Binary Search: " << target << " is not found in file." << std::endl;
    }
    else
    {
        std::cout << "Binary Search: Found in position " << pos2 << std::endl;
    }
    times[55] += times[61]; //Adds the time from merge sort to one instance of the binary search
    v.clear();
    z.clear();
}

void dataEntry(std::string fileName, std::vector<std::string> &v, std::vector<std::string> &z)
{
    std::string word;
    std::ifstream in;
    in.open(fileName);
    while (!in.eof())
    {
        in >> word;
        for (int i = 0; i < word.size(); i++)
        {
            word[i] = tolower(word[i]);
        }
        v.push_back(preProcess(word)); //preProcessing runs first using the string word
                                       //Then that completed word is entered into the vector
    }
    in.close();

    in.open(fileName);
    while (!in.eof())
    {
        in >> word;
        z.push_back(preProcess(word)); //preProcessing runs first using the string word
                                       //Then that completed word is entered into the vector
    }
    in.close();
}

void timeCalculation(double average[], double file[])
{
    int p = 0;
    for (int j = 0; j < 12; j++)
    {
        average[j] = file[p] + file[p + 1] + file[p + 2] + file[p + 3] + file[p + 4];
        p += 5;
        average[j] /= 5;
    }
}

std::string preProcess(std::string word) //Pre Processing function that takes in one word string
{
    std::string wordInput = "";                                                                                                                         //Makes a temporary string that holds final version of whole word
    if (word == "a" || word == "A" || word == "An" || word == "AN" || word == "an" || word == "the" || word == "The" || word == "THe" || word == "THE") //Checks to see if whole word is either a, and the & removes it
    {
        word = "";
    }
    else
    {
        for (int i = 0; i < word.size(); i++)
        {
            if (isalpha(word[i]) || isdigit(word[i])) //Verifies that character of whole string is either a number or part of the alphabet
            {
                wordInput += word[i]; //Adds to temp string
            }
            else if (ispunct(word[i])) //Checks if character is a punctuation
            {
                if (word[i] == '\'') //Ensures that ' and - are kept
                {
                    wordInput += word[i];
                }
                else if (word[i] == '-')
                {
                    wordInput += word[i];
                }
                else //If it is still punctuation but not ' or - & removes it
                {
                    i++;
                }
            }
            else //If character is not punctuation, a number, or part of the alphabet.
            {
                i++;
            }
        }
    }
    return wordInput; //Returns final version of the word
}

void printLast(std::vector<std::string> z) //Print function for last 50 words
{
    for (int i = z.size() - 51; i < z.size(); i++) //Only prints the last 50 words
    {
        std::cout << z[i] << " ";
    }
    std::cout << std::endl;
}

void printFirst(std::vector<std::string> z) //Print function for first 50 words
{
    spaceCleaner(z);
    for (int i = 0; i < 50; i++) //Only prints the first 50 words
    {
        std::cout << z[i] << " ";
    }
    std::cout << std::endl;
}

void swap(std::string &x, std::string &y) //Swap function
{
    std::string temp = x;
    x = y;
    y = temp;
}

int min_position(std::vector<std::string> v, int from, int to)
{
    int min_pos = from; //min pos is in initalized as from var or in this case, next var from selection sort
    for (int i = from + 1; i <= to; i++)
    {
        if (v[i] < v[min_pos]) //if another smallest variable is found
        {
            min_pos = i; //The smallest array position is saved in the min pos variable
        }
    }
    return min_pos; //Returns the min_pos
}

void selection_sort(std::vector<std::string> &v, std::vector<std::string> &z)
{
    int next; // The next position to be set to the minimum

    for (next = 0; next < v.size() - 1; next++)
    {
        int min_pos = min_position(v, next, v.size() - 1); // Find the position of the minimum starting at next
        swap(v[next], v[min_pos]);                         // Swap the next element and the minimum
        swap(z[next], z[min_pos]);
    }
}

void bubble_sort(std::vector<std::string> &v, std::vector<std::string> &z) //Bubble sort function
{
    bool swapped = true;                              //boolean value for seeing whether or not a swap occured
    for (int i = 0; i < v.size() - 1 && swapped; i++) //use condition of swapped to see if the loop needs to be exited
    {
        swapped = false; //set swapped to false to begin with... assuming that the code is unsorted
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]); //swap the two positions if the if-condition is met
                swap(z[j], z[j + 1]);
                swapped = true; //if swap occurred, bool is true
            }
        }
    }
}

void merge(std::vector<std::string> &v, std::vector<std::string> &z, int from, int mid, int to)
{
    int n = to - from + 1; // Size of the range to be merged
    // Merge both halves into a temporary array b
    // We allocate the array dynamically since its size is only
    // known at run time--see Section 7.4
    std::string *b = new std::string[n];
    std::string *c = new std::string[n];

    int i1 = from;
    // Next element to consider in the first half
    int i2 = mid + 1;
    // Next element to consider in the second half
    int j = 0; // Next open position in b

    // As long as neither i1 nor i2 is past the end, move the smaller
    // element into b

    while (i1 <= mid && i2 <= to)
    {
        if (v[i1] < v[i2])
        {
            b[j] = v[i1];
            c[j] = z[i1];
            i1++;
        }
        else
        {
            b[j] = v[i2];
            c[j] = z[i2];
            i2++;
        }
        j++;
    }

    // Note that only one of the two while loops below is executed

    // Copy any remaining entries of the first half
    while (i1 <= mid)
    {
        b[j] = v[i1];
        c[j] = z[i1];
        i1++;
        j++;
    }
    // Copy any remaining entries of the second half
    while (i2 <= to)
    {
        b[j] = v[i2];
        c[j] = z[i2];
        i2++;
        j++;
    }

    // Copy back from the temporary array
    for (j = 0; j < n; j++)
    {
        v[from + j] = b[j];
        z[from + j] = c[j];
    }

    // The temporary array is no longer needed.
    delete[] b;
    delete[] c;
}

void merge_sort(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to)
{
    if (from == to)
    {
        return;
    }
    int mid = (from + to) / 2;
    // Sort the first and the second half
    merge_sort(v, z, from, mid);
    merge_sort(v, z, mid + 1, to);
    merge(v, z, from, mid, to);
}

void insertion_sort(std::vector<std::string> &v, std::vector<std::string> &z, int size)
{
    for (int i = 1; i < size; i++)
    {
        std::string next = v[i];
        std::string next2 = z[i];
        // Move all larger elements up
        int j = i;
        while (j > 0 && v[j - 1] > next)
        {
            v[j] = v[j - 1];
            z[j] = z[j - 1];
            j--;
        }
        // Insert the element
        v[j] = next;
        z[j] = next2;
    }
}

int partition(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to)
{
    std::string pivot = v[from];
    int i = from - 1;
    int j = to + 1;
    while (i < j)
    {
        i++;
        while (v[i] < pivot)
        {
            i++;
        }
        j--;
        while (v[j] > pivot)
        {
            j--;
        }
        if (i < j)
        {
            swap(v[i], v[j]);
            swap(z[i], z[j]);
        }
    }
    return j;
}

void quicksort(std::vector<std::string> &v, std::vector<std::string> &z, int from, int to)
{
    if (from >= to)
    {
        return;
    }
    int p = partition(v, z, from, to);
    quicksort(v, z, from, p);
    quicksort(v, z, p + 1, to);
}

int linear_search(std::vector<std::string> z, int size, std::string value)
{
    for (int i = 0; i < size; i++)
    {
        if (z[i] == value)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(std::vector<std::string> z, int from, int to, std::string value)
{
    if (from > to)
    {
        return -1; 
    }

    int mid = (from + to) / 2;
    if (z[mid] == value)
    {
        return mid;
    }
    else if (z[mid] < value)
    {
        return binary_search(z, mid + 1, to, value);
    }
    else
    {
        return binary_search(z, from, mid - 1, value);
    }
}