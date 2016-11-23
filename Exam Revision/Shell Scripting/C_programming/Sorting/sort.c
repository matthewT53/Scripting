/*
    Name: Matthew Ta
    Date:
    Description: Implementation of the sorting algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sort.h"

#define TRUE 1
#define FALSE 0

#define GAP_SIZE 8 // for shellsort

#define less(x,y) (x < y) // determines whether x is less than y

int numberSwaps = 0;
int numberComparions = 0;

void swap(int *array, const int i, const int j); // swaps two elements in array
int partition(int *array, const int lo, const int high); // for quicksort
void merge(int *array, const int lo, const int mid, const int high);

void selectionSort(int *array, int lo, int high)
{
    int i = 0, j = 0, smallest = 0, smIndex = 0;

    for (i = lo; i < high; i++){
        smallest = array[i];
        smIndex = i; // 3.32 -> ascending 3.305 -> descending
        for (j = high; j > i; j--){
            if (array[j] < smallest){ // cost function
                smallest = array[j];
                smIndex = j;
            }
        }
        swap(array, i, smIndex); // cost function
   }
}

void insertionSort(int *array, int lo, int high)
{
    int i = 0, j = 0, value;

    // find the smallest value in the array
    value = array[lo];
    for ( i = lo + 1; i <= high; i++ ){
        if (array[i] < value){
            j = i;
            value = array[i];
        }
    }

    swap(array, lo, j); // form the sorted part of the array
    
    for ( i = lo + 1; i <= high; i++ ){
        value = array[i];
        for ( j = i; j > lo; j-- ){ // find a place in the sorted array
            if (array[j - 1] < value){ // using the array[j + 1] method overwrites data in the previous positions
                break;
            }

            else{ // shift the array towards the ith pos
                array[j] = array[j - 1];
            }
        }
        array[j] = value;
    }

}

void bubbleSort(int *array, const int lo, const int high)
{
    int i = 0, j = 0;
	int swapped = FALSE;

    for (i = lo; i <= high; i++){
        swapped = FALSE;
        for (j = lo; j <= high - 1; j++){
            if (array[j] > array[j + 1]){ // ascending order
                swap(array, j, j + 1);
                swapped = TRUE;
            }
        }

        // break if list is already sorted
        if (!swapped){
            break;
        }
    }


}

void quicksort(int *array, const int lo, const int high)
{
    int pivot = 0;
    if (lo >= high){ // base case
        return;
    }

    pivot = partition(array, lo, high);
    quicksort(array, lo, pivot - 1);   
    quicksort(array, pivot + 1, high);
}

/*
    Notes:
    * my partition funtion takes too long possibly due to the large numebr of swaps
*/

int partition(int *array, const int lo, const int high)
{
    int value = array[lo];
    int i = lo + 1, j = high;
    
    while (TRUE){
        while (array[i] <= value && i < j){ // find an element larger than pivot
            i++;
        }

        while (value < array[j] && j > i){ // find element smaller than pivot
            j--;
        }

        if (i == j){
            break; // array has been paritioned
        }

        swap(array, i, j); // swap smallest and largest
    }

    // at this point the part of the array has been paritioned
    j = array[i] < value ? i : i - 1;
    swap(array, lo, j);
    return j;
}

/*
int partition(int *array, const int lo, const int high)
{
    int p = lo; // pivot index
    int i = 0, swapped = FALSE;
    
    while(1){
        swapped = FALSE;
        for (i = lo + 1; i < p; i++){ // check from behind pivot
            if (array[i] > array[p]){
                swap(array, i, p);
                p = i;
                swapped = TRUE;
                break;
            }
        }

        for (i = p + 1; i <= high; i++){ // check after pivot
            if (array[i] < array[p]){
                swap(array, i, p);
                p = i;
                swapped = TRUE;
                break;
            }
        }

        if (!swapped){ // break if no swaps performed
            break;
        }

    }

    return p;
}


int partition(int a[], const int lo, const int hi)
{
   int v = a[lo];  // pivot
   int i = lo+1, j = hi;
   for (;;) {
      while (a[i] < v && i < j) i++;
      while (v < a[j] && j > i) j--;
      if (i == j) break;
      swap(a,i,j);
   }
   j = a[i] < v ? i : i-1;
   swap(a,lo,j);
   return j;
}

*/


void mergesort(int *array, const int lo, const int high)
{
    int mid = (lo + high) / 2;

    if (lo >= high) { return; } // base case   
    mergesort(array, lo, mid);
    mergesort(array, mid + 1, high);
    merge(array, lo, mid, high); // merge the two sub arrays
}

/*
    Notes:
    * merge is meant to use extra memory space which makes it more time efficient buts gives it a higher space complexity
    * There is always a space and time tradeoff
*/

void merge(int *array, const int lo, const int mid, const int high) // currently O(n^2)
{
    int i = 0, j = 0, k = 0;
    int arraySize = (high - lo) + 1;
    int *temp = (int *) malloc(sizeof(int) * arraySize);
    
    i = lo;
    j = mid + 1;
    
    // printf("lo = %d, mid = %d and high = %d.\n", lo, mid, high);
    // printf("[BEFORE MERGE]:\n");
    // show(array, lo, high);
    while (k < arraySize && i <= mid){
        while (array[i] >= array[j] && j <= high){
            if (i == mid){
                if (array[i] <= array[j]) { break; }
                else { temp[k++] = array[j++]; }
            }

            else{
                if (array[i + 1] >= array[j]){
                    temp[k++] = array[j++];
                }
            }
        }
        temp[k++] = array[i++];
    }    

    // printf("i = %d and j = %d and k = %d\n", i, j, k);
    while (j <= high) { temp[k++] = array[j++]; }
    while (i <= mid) { temp[k++] = array[i++]; }
    // printf("i = %d and j = %d and k = %d\n", i, j, k);
    
    // copy the temp array into the array
    for (i = lo, k = 0; i <= high; i++, k++){
        array[i] = temp[k];
    } 
    
    // printf("[AFTER MERGE]:\n");
    // show(array, lo, high);

    free(temp);
}


/*
void copy(int a[], int *i, int b[], int *j)
{
	a[*i] = b[*j];
    *i = *i + 1;
    *j = *j + 1;
}


void merge(int a[], const int lo, const int mid, const int hi)
{
   int  i, j, k, nitems = hi-lo+1;
   int *tmp = malloc(nitems*sizeof(int));

   i = lo; j = mid+1; k = 0;
   while (i <= mid && j <= hi) {
     if (a[i] < a[j])
        copy(tmp, &k, a, &i);
	 else
        copy(tmp, &k, a, &j);
   }
   while (i <= mid) copy(tmp, &k, a, &i);
   while (j <= hi) copy(tmp, &k, a, &j);

   //copy back
   for (i = lo, k = 0; i <= hi; i++, k++) {
      a[i] = tmp[k];
   }
   free(tmp);
}*/

// sorts an array using shellsort
void shellsort(int *a, const int lo, const int high)
{
	const int gaps[GAP_SIZE] = {1,4,13,40,121, 364, 1093, 3280}; // gap sizes for comparing the elements
	int i = 0, j = 0, k = 0, g = 0;

	for (k = GAP_SIZE - 1; k >= 0; k--){ // cycle through each gap
		g = gaps[k];
		for (i = g; i <= high; i++){
			for (j = i; j - g >= lo; j -= g){
				if (less(a[j], a[j-g])){
					swap(a, j, j - g);
				}
			}
		}
	}
}

// sorts an array using 
void radixSort(int *a, const int lo, const int hi)
{
	printf("Not implemented yet.\n");
}


void swap(int *array, const int i, const int j)
{
    int temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void show(const int *a, const int lo, const int high)
{
    int i = 0;
    //printf("Showing array.\n");
    for (i = lo; i <= high; i++){
        printf("%d\n", a[i]);
    }
}
