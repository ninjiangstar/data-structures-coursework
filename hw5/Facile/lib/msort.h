#include <vector>
#include <cmath>

using namespace std;

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp){

	mergeSort_Splitter(myArray, 0, myArray.size()-1, comp);

}

template <class T, class Comparator>
void mergeSort_Splitter(vector<T>& a, int l, int r, Comparator comp)
{
	if (l<r) { // otherwise, just one element, which is sorted
		int m = floor((l+r)/2);
		mergeSort_Splitter(a, l, m, comp);
		mergeSort_Splitter(a, m+1, r, comp);
		mergeSort_Merger(a, l, r, m, comp); // this is a separate function given below
	}
}

template <class T, class Comparator>
void mergeSort_Merger (vector<T>& a, int l, int r, int m, Comparator comp)
{
	vector<T> temp;
	// trace through the two subarrays, copying into a temporary one
	int i = l, j = m+1;
	while (i <= m || j <= r) // at least one subarray contains another element
	{
		if (i <= m && (j > r || comp(a[i], a[j])))
		// next smallest element in left subarray
		{ temp.push_back(a[i]); i++; }
		else { temp.push_back(a[j]); j++; }
		// next smallest element in right subarray
	}
	// now copy over the merged array into the original
	for (int k = 0; k < r+1-l; k ++)
		a[k+l] = temp[k];
}