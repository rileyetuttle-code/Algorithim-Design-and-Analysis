#include <iostream>
using namespace std;

/*
  MaxHeap using 1-based indexing.

  - The array `a` stores heap elements in positions [1..n].
  - We first "heapify" by inserting the first i elements, i = 1..n.
  - Then we perform heap sort by repeatedly deleting the max (root)
    and writing it to the end of the array.
*/

template <class T>
class MaxHeap {
private:
    T* a;   // backing array for the heap; we use indices 1..n
    int n;  // total number of elements (not capacity)

public:
    // Construct a heap of given size and read elements from stdin.
    MaxHeap(int size)
    {
        if (size < 0)                    // guard against negative sizes
            throw " size must be greater than zero";

        n = size;                        // total number of elements
        a = new T[n + 1];                // allocate n+1 so we can use a[1..n]

        // Read the n elements. They are placed directly into a[1..n].
        for (int i = 1; i <= n; i++) {
            cout << "\n Enter the element " << i << "\n";
            cin >> a[i];
        }
    }

    // Print the array as it currently sits in memory.
    // Before heapifying this is the input order; after Sort it will be sorted.
    void Display()
    {
        cout << "\nThe array elements are...\n";
        for (int i = 1; i <= n; i++)
            cout << a[i] << "\t";
    }

    // Build the heap incrementally by "inserting" position n into the heap.
    // NOTE: Parameter name `n` here is the index being inserted,
    // not the class member `n`. The caller passes 1, then 2, ..., up to size.
    void Insert(int n);

    // Delete the maximum element from the heap of current size `n`,
    // return it in `x`, then restore the heap property among [1..n-1].
    void DelMax(int n, T& x);

    // Sift-down from index i in a heap of size n to restore heap order.
    void Adjust(int i, int n);

    // Heapsort:
    // 1) Turn the array into a max-heap by calling Insert for i=1..n.
    // 2) Repeatedly remove the max and place it at the end of the array.
    void Sort();
};

// Percolate up: assume positions [1..n-1] already form a valid heap.
// Now "insert" the item currently stored at a[n] into that heap.
template <class T>
void MaxHeap<T>::Insert(int n)
{
    int i = n;        // start at the newly "inserted" leaf index
    T item = a[n];    // the value we need to bubble up

    // While we have not reached the root and the parent is smaller than item,
    // move the parent down and climb up.
    while ((i > 1) && (a[i / 2] < item)) {
        a[i] = a[i / 2];  // move parent down
        i = i / 2;        // move up to parent
    }
    a[i] = item;      // place the item at its correct position
}

// Remove the max (root at a[1]) from a heap of size n.
// Store it in x. Move the last element to the root and sift it down.
template <class T>
void MaxHeap<T>::DelMax(int n, T& x)
{
    if (n == 0) {
        cout << "Heap Empty";
    } else {
        x = a[1];        // the maximum element
        a[1] = a[n];     // move last element to the root
        Adjust(1, n - 1); // restore heap property among the first n-1 elements
    }
}

// Sift-down (heapify) starting at index i in a heap of size n.
// Picks the larger child and moves it up until `item` can be placed.
template <class T>
void MaxHeap<T>::Adjust(int i, int n)
{
    int j = 2 * i;   // left child index
    T item = a[i];   // value we need to place

    while (j <= n) {
        // If right child exists and is larger than left child, use right child.
        if ((j < n) && (a[j] < a[j + 1]))
            j = j + 1;

        // If `item` is already larger than or equal to the bigger child, stop.
        if (item >= a[j]) break;

        // Move the larger child up to the parent position.
        a[j / 2] = a[j];

        // Continue sifting down: jump to the next level's left child.
        j = 2 * j;
    }

    // Place `item` at its final parent position.
    a[j / 2] = item;
}

// Heapsort driver:
// 1) Build a heap by inserting each prefix [1..i].
// 2) Repeatedly extract max and place it at the end (positions i = n..1).
template <class T>
void MaxHeap<T>::Sort()
{
    T x;

    // Phase 1: build a max-heap in-place.
    for (int i = 1; i <= n; i++)
        Insert(i);

    // Phase 2: repeatedly remove the max and write it to the end.
    for (int i = n; i >= 1; i--) {
        DelMax(i, x);                // x gets the current maximum
        cout << "\nint SOrt, value of x is..." << x << "\n";
        a[i] = x;                    // write it at its final sorted position
    }
}

int main()
{
    try {
        MaxHeap<int> m(5);           // read 5 integers from stdin

        cout << "\nBefore Sorting...\n";
        m.Display();

        m.Sort();                    // heapsort in ascending order

        m.Display();                 // show sorted result
    }
    catch (char* c) {                // catches thrown C-style strings
        cout << c;
    }
    return 0;
}
