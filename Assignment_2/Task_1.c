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

#define arraySize 6

int compareCount = 0;
int swapCount = 0;
int DEBUG = 0;  //controls debug messages debug on if = 1; off if = 0



// A utility function to swap two elements
void swap(int *x,int *y){
    int temp;
    if(*x != *y){ //if values are the same DONT swap!!!!!!!!!!!!!!!
    temp = *x;
    *x = *y;
    *y = temp;
    swapCount++;

        if(DEBUG == 1){
            printf("Swapped %d %d \n", *x, *y);
        }
    }
    if(DEBUG == 1){
       printf("No Swapp %d %d \n", *x, *y);
    }

}

int checkSort(int array[], int SIZE){
    int sortCheck = -1;
    
    for(int i = 0; i < SIZE-1 ; i++){
        if(array[i] <= array[i+1]){
            sortCheck = 0;
        }
        else{
            sortCheck = 1;
        }
    } 
    
    return sortCheck;
}

/* Function to print an array */
void printArray(int arr[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
        printf("\n");

}

//Lomuto partition 
int partition (int arr[], int low, int high){ //uses last number as pivot{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= (high - 1); j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot){
            compareCount++;
            i++;    // increment index of smaller element


            swap(&arr[i], &arr[j]);

            if(DEBUG == 1){
                printf("Inside partition_1_1");
                printArray(arr, arraySize);
            }
        }

        if(DEBUG == 1){
            printf("Inside partition_1");
            printArray(arr, arraySize);
        }
        compareCount++;
    }

    swap(&arr[i + 1], &arr[high]); //swap pivot and value after largest value smaller than pivot
    if(DEBUG == 1){
        printf("Inside partition_2");
        printArray(arr, arraySize);
    }
    char s = checkSort(arr, arraySize);

    return (i+1); // return place where pivot was placed
}



/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(int arr[], int low, int high){
    if (low < high)
    {
        int partition_1 = partition(arr, low, high);

        if(DEBUG == 1){
            printf("Inside quicksort");
            printArray(arr, arraySize);
        }

        // Separately sort elements before
        // partition and after partition, recurssively do each side
        quickSort(arr, low, partition_1 - 1);
        quickSort(arr, partition_1 + 1, high);
    }
}


void display(int array[], char test[], int SIZE){
    quickSort(array, 0, (SIZE-1));
    printArray(array, SIZE);
    char s;

    int sortCheck = checkSort(array, arraySize);
    
    if(sortCheck == 0){
         s = 'Y';
    }
    else{
        s = 'N';
    }

    printf("TEST : %s\n" , test);
    printf("Sorted: %c\n", s);
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
    swapCount = 0;
    compareCount = 0;
}


int main( int argc , char *argv[]){

    int arr_URV[] = {4, 3, 5, 1, 0, 2};
    int arr_RV[] = {3, 3, 2, 1, 1, 4};
    int arr_ASL[] = {0, 1, 2, 3, 4, 5};
    int arr_DSL[] = {5, 4, 3, 2, 1, 0};
    int arr_UL[] = {3, 3, 3, 3, 3, 3};
    
    /*quickSort(arr_URV, 0, arraySize);
    printArray(arr_URV, arraySize);

    char sortCheck = checkSort(arr_URV, arraySize);

    printf("TEST : URV\n" );
    printf("Sorted: %c\n", sortCheck);
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);*/

    if(DEBUG == 1){
        printArray(arr_URV, arraySize);
    }

    display(arr_URV, "UniqueRandomValues",  arraySize);
    display(arr_RV, "RandomValues", arraySize);
    display(arr_DSL, "AscendingSortedList", arraySize);
    display(arr_ASL, "DescendingSortedList",  arraySize);
    display(arr_UL, "UniformList", arraySize);
    
    return 0;
}
