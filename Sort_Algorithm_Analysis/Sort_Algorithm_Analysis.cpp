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

void bubbleSort(int* array, int size);

void generateRandomNumbers(int* array);

int maxInt(std::vector<int> vector);

void radixSort(std::vector<int>& vector);

std::vector<int> countSort(std::vector<int>& vector, int place);


//You might want to remove the console ouput of all numbers in each list
//if testing with large numbers of generated integers

int main()
{
    int a[SIZE];
    std::vector<int> b;
    LinkedList list;

    generateRandomNumbers(a);
    for(int i : a){
        std::cout << i << std::endl;//outputs unsorted collection of integers as generated
    }

    std::cout << std::endl;

    int key = 0;
    for (int i : a) {
        b.push_back(i);//populates vector for other sort
        list.newNode(++key, i);//insertion sorted, see LinkedList.cpp
    }

    bubbleSort(a, SIZE);
    //secondSort(b);
    for (int i : a)//comment this block to reduce output
        std::cout << i << std::endl;

    radixSort(b);

    for (int i : b)
        std::cout << i << std::endl;

    list.print();//comment this to reduce output


    int input = 0;//catches the user's input

    return(0);
}

void swap(int& first, int& second) {
    //swaps two integers by reference
    int temp = first;
    first = second;
    second = temp;
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
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % (SIZE * 10);
    }
}

int maxInt(std::vector<int> vector) {
    int max = vector.at(0);
    for (int i : vector) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}
void radixSort(std::vector<int>& vector) {
    /*Sorts a vector of integers by doing a count sort on each 
    place(1, 10, etc) until there are no numbers with the significant figure*/
    int max = maxInt(vector);
    for (int place = 1; max / place > 0; place *= 10) {
        vector = countSort(vector, place);
    }
    //This sort runs log_10(max(n)) times
    //each sub-section runs one full iteration across the vector
    //resulting in time complexity of f(n) = log_10(max(n)) * n
    //f(n) = c * n, or O(n) time complexity.
}

std::vector<int> countSort(std::vector<int>& vector, int place)
{
    /*Sorts a vector of integers into ascending order by the value in a given place(1, 10, etc)
    Uses a hashtable of value counts and an offset by preceding values to determine indicies of placement
    integers with matching significant figures will retain original order*/
    std::vector<int> output;
    output.resize(vector.size());
    int count[10] = { 0 };

    //uses count as a hashtable of counts of which digit(1, 2, ..., 9) is in the nth place(1, 10, etc)
    for (int i = 0; i < vector.size(); i++) {
        count[(vector.at(i) / place) % 10]++;
    }
    //each set will be inserted starting at the position dictated by counts of
    //all numbers with smaller first digits
    //the count vector is reused for this
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    //using the counts in conjunction with the correct place digit, rearrange the values in vector
    //into the correct order in output
    for (int i = vector.size() - 1; i >= 0; i--){
        output.at(count[(vector.at(i) / place) % 10] - 1) = vector.at(i);
        count[(vector.at(i) / place) % 10]--;
    }
    return output;
}