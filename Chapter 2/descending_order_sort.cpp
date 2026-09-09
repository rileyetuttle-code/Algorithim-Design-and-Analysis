#include <iostream>
using namespace std;

void InsertionSortDescending(int A[], int n)
{
    for(int i = 1; i < n; i++) // outer loop that controls the flow of slowly going through the entire array to sort it by 
                                // increasing the starting indice
    {
        int x = A[i];   // x is our key or next value that we use to compare against the already sorted values and see where
                        // it should be placed

        int j = i - 1;  // j is used to be the back/end of our sorted values that we will backtrack through to sort

        while(j >= 0 && A[j] < x) // swapped the equality sign in the comparison of the key (next value) and the value of 
                                    // of where j is backtracking through the sorted area of the array so that it sorts as a comparison of if the key is larger

        {
            A[j + 1] = A[j];    // in descending order case, if the key is larger than the current A[j] this moves that compared A[j] a spot 
                                // to the right to make a gap for the key when it finds its spot
            j--;                // decrement j to backtrack through the sorted values
        }

        A[j + 1] = x;           // when the key finds its spot by being smaller than an already sorted value
    }

}

void Display(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << (i + 1 < n ? ' ' : '\n');
}

int main()
{
    int A[] = {32, -15, 11, 12, 390, -6, 8, 190};
    int n = sizeof(A) / sizeof(A[0]);

    InsertionSortDescending(A, n);
    Display(A, n);

    return 0;
}
