// Merge Sort - full program, with comments explaining the divide-and-conquer
// structure and the merge step.
//
// Big picture (CLRS's three-step recipe):
//   DIVIDE:   split the array into two halves.
//   CONQUER:  recursively sort each half.
//   COMBINE:  merge the two now-sorted halves into one sorted array.
// MSort() does the divide + conquer (recursion). Merge() does the combine.

#include<iostream>
using namespace std;

// Merge assumes A[low..mid] is already sorted AND A[mid+1..high] is already
// sorted (that's the job of MSort's recursive calls before this runs).
// It weaves those two sorted runs together into one sorted run, using
// b[] as scratch space, then copies the result back into a[].
template<class T>
void Merge( T &a, T&b, int low, int mid, int high)
{
	int i=low;    // next free slot to write into in the scratch array b
	int h=low;    // scan pointer into the LEFT run: a[low..mid]
	int j=mid+1;  // scan pointer into the RIGHT run: a[mid+1..high]

	// Walk both runs at once, always taking the smaller of the two
	// "next" candidates. This is the classic two-pointer merge.
	while((h<=mid) && (j<=high))
	{
		if(a[h]<=a[j])
		{
			b[i]=a[h];  // left element is smaller (or equal) -> take it
			h++;
		}
		else
		{
			b[i]=a[j];  // right element is smaller -> take it
			j++;
		}
		i++;
	}

	// By this point, ONE of the two runs is fully drained. We still need
	// to copy over whatever's left of the OTHER run — those leftover
	// elements are already sorted relative to each other, so we just
	// append them as-is (no comparisons needed).
	if(h>mid)
	{
		// Left run exhausted -> drain the rest of the right run.
		for(int k=j;k<=high;k++)
		{
			b[i]=a[k];
			i++;
		}
	}
	else
	{
		// Right run exhausted -> drain the rest of the left run.
		for(int k=h;k<=mid;k++)
		{
			b[i]=a[k];
			i++;
		}
	}

	// b[low..high] now holds the fully merged, sorted sequence.
	// Copy it back into a[], since a[] is the array the rest of the
	// program (and the outer recursive calls) actually reads from.
	for(int k=low;k<=high;k++)
		a[k]=b[k];
}

// MSort recursively sorts a[low..high] using divide-and-conquer.
// b[] is passed along purely as reusable scratch space for Merge,
// so we don't have to allocate new temp arrays at every recursive call.
template<class T>
void MSort(T &a, T &b,int low, int high)
{
	// BASE CASE: low < high is false when low == high (one element,
	// already "sorted") or low > high (empty range). Either way,
	// there's nothing to do.
	if(low<high)
	{
		// DIVIDE: split the range into two halves at mid.
		int mid=(low+high)/2;

		// CONQUER: recursively sort each half independently.
		MSort(a,b,low, mid);      // sort left half  a[low..mid]
		MSort(a,b,mid+1,high);    // sort right half a[mid+1..high]

		// COMBINE: merge the two sorted halves back into one sorted run.
		Merge(a,b,low, mid, high);
	}
}

int main()
{
	int n;
	cout<<"\nEnter the size of array..\n";
	cin>>n;
	int *a= new int[n];
	int *b=new int[n];  // scratch buffer, same size as a, used by Merge
	cout<<"\nEnter the "<<n<<" elements into array\n";
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<"\nElements before sorting are..\n";
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
	cout<<"\n Elemeents after sorting are..\n";

	// Kick off the recursion over the whole array: indices 0..n-1.
	MSort(a,b,0,n-1);

	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
	return 0;

}