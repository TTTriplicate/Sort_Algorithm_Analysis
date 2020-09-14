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


void swap(int& first, int& second);

int* bubbleSort(int* array, int size);

//You might want to remove the console ouput of all numbers in each list
//if testing with large numbers of generated integers

int main()
{
    const int SIZE = 1000;
    int a[SIZE];
    std::vector<int> b;
    int i;
    LinkedList list;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand() % (SIZE * 10);
        std::cout << a[i] << std::endl;//comment this line to reduce output
    }

    std::cout << std::endl;

    int key = 0;
    for (int i : a) {
        b.push_back(i);
        list.newNode(++key, i);
    }

    bubbleSort(a, SIZE);
    //secondSort(b);
    for (int i : a)//comment this block to reduce output
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

int* bubbleSort(int* array, int size) {
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
    return array;
}
