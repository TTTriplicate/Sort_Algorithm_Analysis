/*************************************
Program: Sort_Algorithm_Analysis.cpp
Purpose: Run 3 sorting algorithms 
    for asymptotic analysis
Author: Chris Sousa
Date: 09/12/2020
*****************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "LinkedList.h"

const int SIZE = 100;

void swap(int& first, int& second);
void printVector(std::vector<int> vector);
void printArray(int* array);
void bubbleSort(int* array, int size);
void generateRandomNumbers(int* array);
int maxInt(std::vector<int> vector);
void radixSort(std::vector<int>& vector);
std::vector<int> countSort(std::vector<int> vector, int place);

int main()
{
    int a[SIZE];
    std::vector<int> b;
    LinkedList list;

    generateRandomNumbers(a);

    std::cout << "The numbers as generated:" << std::endl;
    printArray(a);

    int key = 0;
    for (int i : a) {
        b.push_back(i);//populates vector for radix/count sort
        list.newNode(++key, i);//insertion sorted, see LinkedList.cpp
    }

    std::cout << "Bubble Sort:" << std::endl;
    bubbleSort(a, SIZE);
    //secondSort(b);
    printArray(a);
 
    std::cout << "Before Radix Sort:" << std::endl;
    printVector(b);
    
    radixSort(b);

    std::cout << "After Radix Sort:" << std::endl;
    printVector(b);

    std::cout << "After Insertion Sort; IDs represent original order of insertion:" << std::endl;
    list.print();

    return(0);
}

void swap(int& first, int& second) {
    //swaps two integers by reference
    int temp = first;
    first = second;
    second = temp;
}

void printVector(std::vector<int> vector) {
    //prints the contents of a vector<int> in a tab-delimited line
    //Thought it looked good for comparing sort at each iteration
    for (int i : vector) {
        std::cout << i << "\t";
    }
    std::cout << std::endl << std::endl;
}

void printArray(int* array) {
    //prints the contents of an array as a single tab-deliniated line
    for (int i = 0; i < SIZE; i++) {
        std::cout << array[i] << "\t";
    }
    std::cout << std::endl << std::endl;
}

void bubbleSort(int* array, int size) {
    bool changes;//a boolean to track changes for optimization of bubble sort

    for (int j = 0; j < size; j++) {
        changes = false;
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                changes = true;
            }
        }
        if (!changes) {//end the sort if any iteration makes no changes
            break;
        }
    }
}

void generateRandomNumbers(int* array) {
    //Generates SIZE random numbers between 0 and SIZE, and puts them in an array
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % (SIZE * 10);
    }
}

int maxInt(std::vector<int> vector) {
    //returns the maximum integer from the vector argument
    int max = vector.at(0);
    for (int i : vector) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}
void radixSort(std::vector<int>& input) {
    /*Sorts a vector of integers by doing a count sort on each 
    place(1, 10, etc) until there are no numbers with the significant figure*/
    int max = maxInt(input);
    for (int place = 1; max / place > 0; place *= 10) {
        input = countSort(input, place);
        std::cout << "After Count Sort on the " << place << "s place:" << std::endl;
        printVector(input);
    }
    //This sort runs log_10(max(n)) times
    //each sub-section runs one full iteration across the vector
    //resulting in time complexity of f(n) = log_10(max(n)) * n
    //f(n) = c * n, or O(n) time complexity.
}

std::vector<int> countSort(std::vector<int> input, int place)
{
    /*Sorts a vector of integers into ascending order by the value in a given place(1, 10, etc)
    Uses a hashtable of value counts and an offset by preceding values to determine indicies of placement.
    integers with matching significant figures will retain original order*/
    std::vector<int> output;
    output.resize(input.size());
    int digitHashTable[10] = { 0 };

    //generates a hashtable of counts of which digit(1, 2, ..., 9) is in the nth place(1, 10, etc)
    for (int i = 0; i < input.size(); i++) {
        digitHashTable[(input.at(i) / place) % 10]++;
    }
    //each set will be inserted starting at the position dictated by counts of
    //all numbers with smaller first digits
    //the hashtable is modified in place for this 
    for (int i = 1; i < 10; i++) {
        digitHashTable[i] += digitHashTable[i - 1];
    }
    //using the counts in conjunction with the correct place digit, rearrange the values in input
    //into the correct order in output
    for (int i = input.size() - 1; i >= 0; i--){
        output.at(digitHashTable[(input.at(i) / place) % 10] - 1) = input.at(i);
        digitHashTable[(input.at(i) / place) % 10]--;
    }
    return output;
}