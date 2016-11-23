/*
    Name: Matthew Ta
    Date:
    Descrip: Prototypes for my own implementation of the sorting algorithms
*/

void selectionSort(int *array, int lo, int high);

void insertionSort(int *array, int lo, int high);

void bubbleSort(int *array, const int lo, const int high);

void quicksort(int *array, const int lo, const int high);

void mergesort(int *array, const int lo, const int high);

void shellsort(int *array, const int lo, const int high);

void radixSort(int *array, const int lo, const int high);

// helper functions
void show(const int *a, const int lo, const int high);
