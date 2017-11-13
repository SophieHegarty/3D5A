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

#define compareCount = 0;
#define swapCount = 0;

// A utility function to swap two elements
void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    swapCount++
}


int partition (int arr[], int low, int high) //uses last number as pivot
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            compareCount++;
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
        compareCount++;
    }
    swap(&arr[i + 1], &arr[high]); //swap pivot and value after largest value smaller than pivot
    return (i + 1); // return place where pivot was placed
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
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
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}

int checkArray(int arr[], int SIZE){
    int sortCheck = -1;
    for(int i =0; i < SIZE -1; i++){
        if(arr[i] <= arr[i+1]){
            sortCheck = 0;
        }
        else{
            sortCheck = 1;
        }
    }
    return sortCheck;
}


int main()
{
    int SIZE = 10;
    int arr[] = {10, 7, 8, 9, 1, 5, 12, 15, 3, 11};
    
    quickSort(arr, 0, SIZE);
    printArray(arr, SIZE);
    
    int sort = checkArray(arr, SIZE);
    char s;
    if(sort == 0){
        s = 'Y';
    }
    else{
        s = 'N';
    }

    
    printf("TEST : ARRAY");
    printf("Sorted: %c\n", s); //add check
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
    printArray(arr, SIZE);
    return 0;
}

