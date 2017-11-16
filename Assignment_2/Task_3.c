//
//  Task_3.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 16/11/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arraySize 15
#define MAX_BUFFER 256 // Maximum string length this program can handle

int dEBUG = 0;  //controls debug messages debug on if = 1; off if = 0


struct Game {
    int score, releaseYear;
    char title[MAX_BUFFER], platform[MAX_BUFFER];
};

struct Game game[MAX_BUFFER];

// The CSV parser
int
next_field( FILE *f, char *buf, int max ) {
    int i=0, end=0, quoted=0;
    
    for(;;) {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        // end of field on comma if we're not inside quotes
        if(buf[i]==',' && !quoted) { break; }
        // end record on newline or end of file
        if(feof(f) || buf[i]=='\n') { end=1; break; }
        // truncate fields that would overflow the buffer
        if( i<max-1 ) { ++i; }
    }
    
    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}

// Stuff to make life a bit neater in main
void fetch_game( FILE *csv, struct Game *g) {
    char buf[MAX_BUFFER];
    
    next_field( csv, g->title, MAX_BUFFER );
    next_field( csv, g->platform, MAX_BUFFER );
    next_field( csv, buf, MAX_BUFFER );
    g->score = atoi(buf);
    next_field( csv, buf, MAX_BUFFER );
    g->releaseYear = atoi(buf);
    
}

void print_game( struct Game *g ) {
    printf("  %i %s %s %i\n", g->score, g->title, g->platform, g->releaseYear );
    
}

/////////////////////////////////////// SORTING BELOW  ////////////////////////////////////////////////
// A utility function to swap two elements
void swap(int *x,int *y){
    int temp;
    if(*x != *y){ //if values are the same DONT swap!!!!!!!!!!!!!!!
        temp = *x;
        *x = *y;
        *y = temp;
        //swapCount++;
        
        if(dEBUG == 1){
            printf("Swapped %d %d \n", *x, *y);
        }
    }
    if(dEBUG == 1){
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
int partition (struct Game *arr, int low, int high){ //uses last number as pivot{
    int pivot = arr[high].score;    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= (high - 1); j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].score <= pivot){
            //compareCount++;
            i++;    // increment index of smaller element
            
            
            swap(&arr[i].score, &arr[j].score);
            
            if(dEBUG == 1){
                printf("Inside partition_1_1");
                //printArray(arr, arraySize);
            }
        }
        
        if(dEBUG == 1){
            printf("Inside partition_1");
            //printArray(arr, arraySize);
        }
        //compareCount++;
    }
    
    swap(&arr[i + 1].score, &arr[high].score); //swap pivot and value after largest value smaller than pivot
    if(dEBUG == 1){
        printf("Inside partition_2");
        //printArray(arr, arraySize);
    }
    //char s = checkSort(arr, arraySize);
    
    return (i+1); // return place where pivot was placed
}



/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(struct Game *arr, int low, int high){
    if (low < high)
    {
        int partition_1 = partition(arr, low, high);
        
        if(dEBUG == 1){
            printf("Inside quicksort");
            //printArray(arr, arraySize);
        }
        
        // Separately sort elements before
        // partition and after partition, recurssively do each side
        quickSort(arr, low, partition_1 - 1);
        quickSort(arr, partition_1 + 1, high);
    }
}


/*void display(int array[], char test[], int SIZE){
 quickSort(array, 0, (SIZE-1));
 if(DEBUG == 1){
 printArray(array, SIZE);
 }
 int sortCheck = checkSort(array, arraySize);
 char s;
 if(sortCheck == 0){
 s = 'Y';
 }
 else{
 s = 'N';
 }
 printf("TEST:     %s\n" , test);
 printf("SORTED:   %c\n", sortCheck);
 printf("SWAPS:    %i\n", swapCount);
 printf("COMPARES: %i\n", compareCount);
 swapCount = 0;
 compareCount = 0;
 }*/

int main ( int argc, char *argv[] ) {
    FILE *f;
    struct Game g;
    int count = 0;
    f = fopen("/User/sophiehegarty/Documents/Trinity Engineering/ TCD JS/ Data Structures and Algorithms/Assignment_2/Assignment_2/truncated.csv", "r");
    int i = 0;
    printf("WHY THE FUCK AM I NOT GETTING A PRINT OUT");
    
    if (f==NULL) {
        printf("Error opening file");
    }
    
    //fetch_game( f, &g ); // discard the header data in the first line
    
    // Now read and print pokemon until the end of the file
    while(!feof(f)) {
        fetch_game( f, &g );
        game[i] = g;
        count++;
        //print_game( &g );
        //printf("\n");
    }
    
    while(!feof(f)){
        print_game( &g );
        printf("\n");
    }
    
    
    // Always remember to close the file
    fclose(f);
    return EXIT_SUCCESS;
}
