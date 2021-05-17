#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

void printVector(vector<int> vec)
{
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

void printArray(int *A, int size)
{
    for (int i = 0; i <= size; i++)
    {
        if (A[i] != INT_MAX)
        {
            cout << A[i] << " ";
        }
        else
        {
            cout << "i ";
        }
    }
    cout << endl;
}

void printMatrix(int **M, int n, int m)
{
    for (int i = 0; i <= n; i++)
    {
        printArray(M[i], m);
    }
}

#endif