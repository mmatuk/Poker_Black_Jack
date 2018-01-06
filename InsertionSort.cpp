//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  InsertionSort.cpp
//Description:
//
//Editor:                          Emacs
//*******************************************************

#include <iostream>

template <typename T>
void insertionSort(T *values[], int const size) // insertion sort algorithm
{
  T *key;
  for (int j = 1; j < size; j++)
  {
    // each for loop
    key = values[j];
    int i = j - 1;

    // when while does not run
    while (i >= 0 && *values[i] > *key) // While number is bigger then key
    {
      // when while runs
      values[i + 1] = values[i];
      i--;
    }
    values[i + 1] = key;
  }
}
