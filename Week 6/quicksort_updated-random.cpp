// Quick Sort (Hoare partition)
// quicksort.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;

template <class T>
void Display(const T A[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << A[i] << "   ";
    }
}
template <class T>
void swapdata (T *x, T *y)

{
    T temp;
    temp = *x;
    *x = *y;
    *y= temp;
}

template <class T>
int Partition(T A[], int low, int high, int &randIndex) {

    swapdata(&A[low], &A[randIndex]); // swap random and low so that the random variable is now our pivot variable but that it still works with the origninal
                                    // algorithim that assumes the pivot is low and keeps i and j in bounds 

    T pivot = A[low];          // choose first element as pivot
    int i = low - 1;//If you set i = low, the very first ++i jumps to low + 1. You never inspect A[low] in the left scan.
    int j = high + 1;
                    //If you set j = high, the very first --j jumps to high - 1. You never inspect A[high] in the right scan.
    

    do 
    {
        do { i++; } while (A[i] < pivot); //take care the duplicates that why not <=
        do { j--; } while (A[j] > pivot);
        if (i < j) 
            swapdata(&A[i], &A[j]);
    }
    while (i<j);
    swapdata (&A [low], &A[j]); // pivot swapping with j (high) to get to its final partition place
    return j;
}

template <class T>
void QuickSort(T A[], int low, int high) {

    int randIndex = low + rand() % (high - low + 1);

    if (low < high) {
        int j = Partition(A, low, high, randIndex);
        QuickSort(A, low, j);
        QuickSort(A, j + 1, high);
    }
}

int main() {
    //int A[] = {32, -15, 115, 12, 300, -6, 8, 190, 77,32,115, 3, 38, 20, 20, 33, 234, 56, 92, 45, 80, 10, 37, 98, 90, 31, 78, 89, 289, 120, 378, 82, 157}; // large array
    int A[] = {32, -15, 115, 12, 300, -6}; // small array
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Before Sorting:\n";
    Display(A, n);
    cout << endl;

    // measure quicksort time
    auto startQuickSort = chrono::high_resolution_clock::now();
    QuickSort(A, 0, n - 1);
    auto stopQuickSort = chrono::high_resolution_clock::now();

    auto durationQuickSort =
        chrono::duration_cast<chrono::nanoseconds>(stopQuickSort - startQuickSort);

    cout << "\nAfter Sorting:\n";
    Display(A, n);
    cout << endl;
    cout << "Time Taken: " << durationQuickSort.count() << " nanoseconds" << endl << endl;

    return 0;
}
