#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define array_size 18625
#define MAX_BUFFER 100

int dEBUG = 0;

typedef struct Game Game;

struct Game {
 
    char title[MAX_BUFFER], platform[MAX_BUFFER];
       int score, releaseYear;
};

Game games[array_size];

int next_field( FILE *f, char *buf, int max ) {
    int i=0, end=0, quoted=0;
    
    for(;;) {
        buf[i] = fgetc(f);
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        if(buf[i]==',' && !quoted) { break; }
        if(feof(f) || buf[i]=='\n') { end=1; break; }
        if( i<max-1 ) { ++i; }
    }
    
    buf[i] = 0;
    return end;
}

void fetch_Game (FILE *csv, struct Game *g) {
    char buf[MAX_BUFFER];
    
    next_field(csv, g->title, MAX_BUFFER);
    
    next_field(csv, g->platform, MAX_BUFFER);
    
    next_field(csv, buf, MAX_BUFFER);
    g->score = atoi(buf);
    
    next_field(csv, buf, MAX_BUFFER);
    g->releaseYear = atoi(buf);
    
}
void print_game( struct Game *g ) {
    printf("  %i %s %s %i\n", g->score, g->title, g->platform, g->releaseYear );
    
}
int swap_num = 0;
int comparison = 0;

/////////////////////////////////////// SORTING BELOW  ////////////////////////////////////////////////
// A utility function to swap two elements
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
void quicksort(Game *A, int low, int high){

    if (low < high){
        int partition_1 = partition(A, low, high);
        
        quicksort(A, low, partition_1-1);
        quicksort(A, partition_1+1, high);
        
    }
    
}

int main ( int argc, char *argv[] ) {
    FILE *csv;
    Game g;
    int i = 0;
    
    csv = fopen ("ign.csv","r");
    
    if (csv==NULL) {
        perror ("Error opening file");
    }
    
    fetch_Game(csv, &g);
    
    
    while(!feof(csv)){
        fetch_Game(csv, &g);
        games[i] = g;
        i++;
    }
    
    quicksort(games, 0,(array_size - 1));

    for(int i = 0; i < array_size-1; i++){
        print_game(&games[i]);
    }
    
    printf("Print\n");

    
    
    fclose(csv);
    return EXIT_SUCCESS;
}
