#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

// Generate random array with values in [lower_bound, upper_bound]
void generateRandomArray(int arr[], int size, int lower_bound, int upper_bound) {
    for (int i = 0; i < size; i++) {
        arr[i] = lower_bound + (rand() % (upper_bound - lower_bound + 1));
    }
}

// Function for Insertion Sort (in-place)
void insertionSort(int arr[], int size) 
{
    for (int i = 1; i < size; i++)
    {
        int x = arr[i];

        int j = i - 1;

        while(j >= 0 && x < arr[j])
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j + 1] = x;
    }
}

// Merge helper for Merge Sort
void merge(int temp[], int arr[], int left, int mid, int right) 
{
    temp[right + 1];
    int i = left;
    int h = left;
    int j = mid + 1;

    while((h <= mid) && (j <= right)) // comparing the left and right split array sections and adding the smaller values into the temp array
    {
        if(arr[h] <= arr[j])
        {
            temp[i] = arr[h];
            h++;
        }
        else
        {
            temp[i] = arr[j];
            j++;
        }
        i++;
    }

    if(h > mid) // comparison between the two has been done by the while loop, so just copy over the leftover values to attach them to the temp array 
                // based on which ever side finished first
    {
        for(int k=j; k <= right; k++)
        {
            temp[i] = arr[k];
            i++;
        }
    }
    else
    {
        for(int k = h; k <= mid; k++)
        {
            temp[i] = arr[k];
            i++;
        }
    }

    // loop to merge them together at the end after fully sorted
    for(int k = left; k <= right; k++)
    {
        arr[k] = temp[k];
    }
}

// Function Merge Sort 
void mergeSort(int temp[], int arr[], int left, int right) 
{
    if (left < right) // base case for when nums get broken down into just themselves (left == right) which means they are headed to be sorted
    {
        int mid = (left + right) / 2;

        mergeSort(temp, arr, left, mid);
        mergeSort(temp, arr, mid + 1, right);

        merge(temp, arr, left, mid, right);

    }
}

// Print array as comma-separated list
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << (i < size - 1 ? "," : "");
    }
    cout << endl;
}

//Main Function
int main() {
    int size; // create size variable to ask user for size of array
    int *temp = new int[size + 1]; // declare the temp array in main so it saves space and doesn't call it everytime merge sort is called

    cout << "Enter the size of the array: "; // prompt user for size input
    cin >> size;

    // declare and initialize all 3 dynamically allocated arrays to allow for the runtime determined size from the user to set in the arrays
    int *arr = new int[size];
    int *arrForInsertion = new int[size];
    int *arrForMerge = new int[size];
    
    // Seed RNG and generate numbers in [1, 1000]
    srand(static_cast<unsigned>(time(nullptr)));
    generateRandomArray(arr, size, 1, 1000);

    // Make copies for fair comparison
    copy(arr, arr + size, arrForInsertion);
    copy(arr, arr + size, arrForMerge);

    cout << "Original array:\n";
    printArray(arr, size);

    // Measure Insertion Sort
    auto startInsertion = chrono::high_resolution_clock::now();
    insertionSort(arrForInsertion, size);
    auto stopInsertion = chrono::high_resolution_clock::now();
    auto durationInsSort =
        chrono::duration_cast<chrono::microseconds>(stopInsertion - startInsertion);

    // Measure Merge Sort
    auto startMerge = chrono::high_resolution_clock::now();
    mergeSort(temp, arrForMerge, 0, size - 1);
    auto stopMerge = chrono::high_resolution_clock::now();
    auto durationMergeSort =
        chrono::duration_cast<chrono::microseconds>(stopMerge - startMerge);

    // Display results
    cout << "\nAfter Insertion Sort:\n";
    printArray(arrForInsertion, size);
    cout << "Insertion Sort time: " << durationInsSort.count() << " microseconds\n";

    cout << "\nAfter Merge Sort:\n";
    printArray(arrForMerge, size);
    cout << "Merge Sort time: " << durationMergeSort.count() << " microseconds\n";

    // Optional: a quick verdict for this run
    cout << "\nFaster this run: "
         << ((durationInsSort.count() < durationMergeSort.count()) ? "Insertion Sort" : "Merge Sort")
         << endl;

    // deallocate memory of the arrays
    delete[] arr;
    delete[] arrForInsertion;
    delete[] arrForMerge;

    return 0;
}
