// Quick Sort (Hoare partition)
// quicksort.cpp
#include <iostream>
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
int Partition(T A[], int low, int high) {
    T pivot = A[low];          // choose first element as pivot
    int i = low - 1;//If you set i = low, the very first ++i jumps to low + 1. You never inspect A[low] in the left scan.
    int j = high + 1;
                    //If you set j = high, the very first --j jumps to high - 1. You never inspect A[high] in the right scan.
    

    do 
    {
        do { i++; } while (A[i] < pivot);//take care the duplicates that why not <=
        do { j--; } while (A[j] > pivot);
        if (i < j) 
            swapdata(&A[i], &A[j]);
    }
    while (i<j);
    swapdata (&A [low], &A[j]);
    return j;
}

template <class T>
void QuickSort(T A[], int low, int high) {
    if (low < high) {
        int j = Partition(A, low, high);
        QuickSort(A, low, j);
        QuickSort(A, j + 1, high);
    }
}

int main() {
    int A[] = {32, -15, 115, 12, 300, -6, 8, 190, 77,32,115};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Before Sorting:\n";
    Display(A, n);

    QuickSort(A, 0, n - 1);

    cout << "\nAfter Sorting:\n";
    Display(A, n);
    return 0;
}
