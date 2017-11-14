//
//  Task_10000.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 13/11/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define arraySize 7

int compareCount = 0;
int swapCount = 0;
int DEBUG = 1;

/////////////////////////// FILL ARRAYS /////////////////////////
void shuffle(int *arr, size_t n){
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL)); //set seed value
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

void fill_URV(int array[]){
     for (int i = 0; i < arraySize; i++){
        array[i] = i;
    }
    shuffle(array, arraySize);
}

void fill_RV(int array[]){
     srand(0); //set seed value

    for (int i = 0; i < arraySize; i++) {
        array[i] = rand()%100;
    }
}

void fill_ASL(int array[]){
    srand(0); //set seed value

    for (int i = 0; i < arraySize; i++) {
        array[i] = i;
    }
}

void fill_DSL(int array[]){
    //srand(0); //set seed value

    for (int i = arraySize; i >= 0; i--) {
        array[i] = i;
    }
}

void fill_UL(int array[]){
         srand(0); //set seed value
         int num = rand();

    for (int i = 0; i < arraySize; i++) {
        //array[i] = num;
        array[i] = 8;
    }
}

/////////////////////////////////////////////////////////////////////////////////

void swap(int *x, int *y)
{
    if(*x != *y){
        int temp = *x;
        *x = *y;
        *y = temp;
        swapCount++;
    }
}

void selectionSort(int arr[]){
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < arraySize-1; i++){
	    compareCount++;
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < arraySize; j++){
		    compareCount++;
            if (arr[j] < arr[min_idx]){
            //compareCount++;
                min_idx = j;
            }
        }
		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

char checkSort(int array[], int SIZE){
    int sortCheck = -1;
    char s;
    
    for(int i = 0; i < SIZE-1 ; i++){
        if(array[i] <= array[i+1]){
            sortCheck = 0;
        }
        else{
            sortCheck = 1;
        }
    } 
    if(sortCheck == 0){
         s = 'Y';
    }
    else{
        s = 'N';
    }
    return s;
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void display(int array[], char test[]){
    selectionSort(array);
    if(DEBUG == 1){
        printArray(array, arraySize);
    }
    //printArray(array, arraySize);

    char sortCheck = checkSort(array, arraySize);

    printf("TEST:     %s\n" , test);
    printf("SORTED:   %c\n", sortCheck);
    printf("SWAPS:    %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
    swapCount = 0;
    compareCount = 0;
}

// Driver program to test above functions
int main()
{
	int arr_URV[arraySize];
    int arr_RV[arraySize];
    int arr_ASL[arraySize];
    int arr_DSL[arraySize];
    int arr_UL[arraySize];
    
    fill_URV(arr_URV);
    fill_RV(arr_RV);
    fill_ASL(arr_ASL);
    fill_DSL(arr_DSL);
    fill_UL(arr_UL);

    if(DEBUG == 1){
        printArray(arr_RV, arraySize);
    }

    display(arr_URV, "UniqueRandomValues");
    display(arr_RV, "RandomValues");
    display(arr_ASL, "AscendingSortedList");
    display(arr_DSL, "DescendingSortedList");
    display(arr_UL, "UniformList");

}