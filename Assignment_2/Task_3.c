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

#define arraySize 6

int compareCount = 0;
int swapCount = 0;
int DEBUG = 0;  //controls debug messages debug on if = 1; off if = 0

typedef struct  Game Game;
struct Game {
    char Title;
    char Platform;
    int Score;
    int releaseYear;
    
};



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

    char sortCheck = checkSort(array, arraySize);

    printf("TEST : %s\n" , test);
    printf("Sorted: %c\n", sortCheck);
    printf("SWAPS: %i\n", swapCount);
    printf("COMPARES: %i\n", compareCount);
    swapCount = 0;
    compareCount = 0;
}

// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { break; } // only load letters and numbers
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement( buf);                           //here you call your function from above!
	}

	// always remember to close your file stream
	fclose(f);

	return 1;
}


int main( int argc , char *argv[]){

    Game buffer[arraySize];


    
    return 0;
}
