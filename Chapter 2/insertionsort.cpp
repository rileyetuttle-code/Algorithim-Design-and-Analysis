// Insertion Sort - full program, with comments mapping back to CLRS pseudocode.
//
// CLRS pseudocode (1-indexed) looks like:
//   for j = 2 to A.length
//       key = A[j]
//       i = j - 1
//       while i > 0 and A[i] > key
//           A[i+1] = A[i]
//           i = i - 1
//       A[i+1] = key
//
// This C++ version is 0-indexed, so every index is shifted down by 1:
//   CLRS j   -> here i
//   CLRS key -> here x
//   CLRS i   -> here j
// Same algorithm, same logic, just different starting point and names.

#include <iostream>
using namespace std;

// Prints the array on one line, space-separated.
void Display(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << (i + 1 < n ? ' ' : '\n');
}

void InsertionSort(int A[], int n)
{
    // Outer loop: i marks the "next card to pick up" from the unsorted pile.
    // KEY INVARIANT: at the start (and end) of every outer loop iteration,
    // A[0..i-1] is already sorted. i = 1 is the smallest useful start,
    // because a single element A[0] is trivially "sorted" on its own —
    // there's nothing to compare it against yet.
    for (int i = 1; i < n; i++)
    {
        // x is the element we're about to insert into the sorted region.
        // We save it in a variable first because the shifting below will
        // overwrite A[i]'s original slot.
        int x = A[i];

        // j starts just to the left of x, and will walk backward through
        // the sorted region A[0..i-1] looking for where x belongs.
        int j = i - 1;

        // Shift (NOT swap) every element bigger than x one slot to the
        // right, opening up a gap. We stop when we hit an element <= x,
        // or run off the left edge of the array (j < 0).
        while (j >= 0 && A[j] > x)
        {
            A[j + 1] = A[j];  // slide the bigger element right
            j--;              // keep walking left
        }

        // Loop exits when A[j] <= x (or j == -1, meaning x is the new
        // smallest element). Either way, the gap at j+1 is exactly where
        // x belongs. Drop it in.
        A[j + 1] = x;

        // After this iteration, A[0..i] is sorted — invariant restored,
        // one element bigger.
    }
}

int main()
{
    int A[] = {32, -15, 11, 12, 390, -6, 8, 190};
    int n = sizeof(A) / sizeof(A[0]);

    InsertionSort(A, n);
    Display(A, n);

    return 0;
}