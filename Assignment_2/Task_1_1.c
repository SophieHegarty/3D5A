//
//  Task_1.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 13/11/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>



// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
 the pivot element at its correct position in sorted
 array, and places all smaller (smaller than pivot)
 to left of pivot and all greater elements to right
 of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
         at right place */
        int pi = partition(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

// Driver program to test above functions
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("Sorted array: n");
    printArray(arr, n);
    return 0;
}




#include <stdio.h>
#include <stdlib.h>

void swap(int *x,int *y);
int choose_pivot(int i,int j );
void quicksort(int list[],int m,int n);
void display(int list[],const int n);

void main()
{
    const int SIZE = 10;
    int list[SIZE] = {13,4,67,68,34,12,7,1,19,13};
    
    //int i = 0;
    
    /* generates random numbers and fill the list */
    //for(i = 0; i < SIZE; i++ )
    //  list[i] = rand();
    
    printf("The list before sorting is:\n");
    display(list,SIZE);
    
    /* sort the list using quicksort algorithm */
    quicksort(list,0,SIZE-1);
    
    printf("The list after sorting:\n");
    display(list,SIZE);
}

void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int choose_pivot(int i,int j )
{
    return((i+j) /2);
}

void quicksort(int list[],int m,int n)
{
    int key,i,j,k;
    if( m < n)
    {
        k = choose_pivot(m,n);
        printf("%i\n", k);
        swap(&list[m],&list[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j)
                swap(&list[i],&list[j]);
        }
        /* swap two elements */
        swap(&list[m],&list[j]);
        
        /* recursively sort the lesser list */
        quicksort(list,m,j-1);
        quicksort(list,j+1,n);
    }
}
void display(int list[],const int n)
{
    int i;
    for(i=0; i<n; i++){
        printf("%d\t",list[i]);
    }
    printf("\n");
}




//
//  Task_1.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 30/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

//add implementation

/*#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdbool.h>
 
 #define compareCount = 0;
 #define swapCount = 0;
 
 
 /////////////////////////////////////
 
 //NOTE:
 //easier to add functions for compare and swap than add in ++; global counters
 //dont use bubblesort in part 2
 
 /////////////////////////////////////
 
 
 int next_field(FILE *csv, char *buffer, int max_length){
 char current = fgetc(csv);  //get character from the csv file, set as current character
 int i = 0;
 int value;
 bool quote;
 
 
 if(current == '"'){
 quote = true;
 }else
 {
 quote = false;}
 
 while(current != EOF && current != ',' && current != '\n' && quote == false){
 buffer[i] = current;
 current = fgetc(csv);
 i++;
 }
 
 if(current == '"'){
 
 }
 if(quote == true && current == ','){
 buffer[i] = current;
 current = fgetc(csv);
 i++;
 }
 else if(current == ',' && quote != true){    //if curretn character = , then but 0 in buffer and return 0
 buffer[i] = '\0';
 value = 0;
 }
 else if(current == '\n' || current == EOF){   //if current character = new line, load 0 into buffer and return 1
 buffer[i] = '\0';
 value = 1;
 }
 return value;
 
 }
 
 void swap(int *x,int *y)
 {
 int temp;
 temp = *x;
 *x = *y;
 *y = temp;
 }
 
 int choose_pivot(int i,int j )
 {
 return((i+j) /2);
 }
 
 void quicksort(int list[],int m,int n)
 {
 int key,i,j,k;
 if( m < n)
 {
 k = choose_pivot(m,n);
 printf("%i\n", k);
 swap(&list[m],&list[k]);
 key = list[m];
 i = m+1;
 j = n;
 while(i <= j)
 {
 while((i <= n) && (list[i] <= key))
 i++;
 while((j >= m) && (list[j] > key))
 j--;
 if( i < j)
 swap(&list[i],&list[j]);
 }
 /* swap two elements */
//swap(&list[m],&list[j]);

/* recursively sort the lesser list */
/*quicksort(list,m,j-1);
 quicksort(list,j+1,n);
 }
 }
 
 void display(int list[],const int n)
 {
 int i;
 for(i=0; i<n; i++)
 printf("%d\t",list[i]);
 }
 
 int main()
 {
 const int SIZE = 10;
 int list[SIZE];
 
 int i = 0;
 
 /* generates random numbers and fill the list */
/* for(i = 0; i < SIZE; i++ )
 list[i] = rand();
 
 printf("The list before sorting is:\n");
 display(list,SIZE);
 
 /* sort the list using quicksort algorithm */
/*quicksort(list,0,SIZE-1);
 
 printf("The list after sorting:\n");
 display(list,SIZE);
 
 return 0;
 }*/

