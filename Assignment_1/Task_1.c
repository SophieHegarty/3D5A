//
//  Task_1.c
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

#define compareCount 0
#define swapCount 0
#define arraySize 10


// A utility function to swap two elements
void swap(int *x,int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    swapCount++
}


int partition (int arr[], int low, int high) //uses last number as pivot{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= high- 1; j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot){
            //compareCount++;
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
        //compareCount++;
    }
    swap(&arr[i + 1], &arr[high]); //swap pivot and value after largest value smaller than pivot
    return (i + 1); // return place where pivot was placed
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(int arr[], int low, int high){
    if (low < high)
    {
        int partition_1 = partition(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, partition_1 - 1);
        quickSort(arr, partition_1 + 1, high);
    }
}

/* Function to print an array */
void printArray(int arr[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
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


void display(int array[], char test[], int SIZE){
    quickSort(array, 0, SIZE);
    printArray(array, SIZE);

    char sortCheck = checkSort(array, arraySize);

    printf("TEST : %s\n" , test);
    printf("Sorted: %c\n", sortCheck);
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
}


int main()
{

    int arr_URV[] = {10, 7, 8, 9, 1, 5, 12, 15, 3, 11};
    int arr_RV[] = {10, 7, 8, 9, 7, 5, 10, 15, 3, 11};
    int arr_ASL[] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17};
    int arr_DSL[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr_UL[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    
    quickSort(arr_URV, 0, arraySize);
    printArray(arr_URV, arraySize);

    char sortCheck = checkSort(arr_URV, arraySize);

    printf("TEST : URV\n" );
    printf("Sorted: %c\n", sortCheck);
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
    
    return 0;
}
