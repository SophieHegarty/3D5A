//
//  Task_1.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 30/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
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

void partition(array[], low, high){
    *temp;
    *low;
    *high;

    

}

int swap(a, b){
    buffer[a] = buffer[b];
    buffer[b] = buffer[a];
    swapCount++; 
}

int compare(a, b){
    
}; 



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

int  main ( int argc , char *argv[] )
{






    return 0;
}