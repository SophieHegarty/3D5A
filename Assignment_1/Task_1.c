//
//  Task_1.c
//  Assignment_1_1
//
//  Created by Sophie Hegarty on 26/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 50 //max length of a string
#define ARRAY_SIZE 211  //best be prime

typedef struct  Element Element;
struct Element
{
    char name[MAX_STRING_SIZE];
    int count;
};

struct Element* hashTable[ARRAY_SIZE];

int hash(char* s){
    int hash = 0;
    while(*s)
    {
        hash = (hash + *s) % ARRAY_SIZE;
        s++;
    }
    return hash;
}


void createElement(char* name, int position){
    struct Element *new = (Element*)malloc(sizeof(Element)); //allocate new memory for element
    strcpy(new -> name, name); //copy name that is passed through to the 'new' name in the struct
    new -> count = 1; //set count to 1 as name occurs once for now
    hashTable[position] = new;  //place the name into the postion on the hastable acccording to hashno
}

void initialiseArray(){ // initialoze array
    int i;
    char* dummy_name = "\0"; //dummy variable, set it to NULL
    
    for(i=0; i<ARRAY_SIZE; i++) //loop thorugh
    {
        createElement(dummy_name,i); //set all buckets to null, within the arraysize
        hashTable[i]->count = 0; //set
    }
}


int collisions = 0; //gloabl variable for no. of collisions


int search(char* name, int *key){
    int value = -1; //bool to be returned
    int i;  //dummy variable
    int hashNumber = hash(name); //get hash number
    
    if(strcmp(hashTable[hashNumber]->name, name) == 0){ //if search name == name in bucket return 1
        
        *key = hashNumber; //set key/index to hashNumber
        value = 1;
    }
    else if(strcmp(hashTable[hashNumber]->name , "\0") == 0){ //if NULL in bucket return 0
        
        *key = hashNumber; //set key/index to hashNumber
        value = 0;
    }
    else{
        i = hashNumber;
        while(strcmp(hashTable[i]->name, "\0") != 0){ //while name isn't NULL value --- collisions -----
            
            i++; //increase hash by 1 and try again
            collisions++; //increase collision number by 1
            if(i == ARRAY_SIZE){ //if reached end of array, start at hashtable[0]
                i = 0;
            }
        }
        *key = i;
        value = 0;
    }
    return value;
}

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
    FILE *csv_file;
    csv_file = fopen("names.csv", "r");  //read in csv file
    //char data[1024];     //array storing data
    char buffer[MAX_STRING_SIZE];
    int position;
    initialiseArray(); //set all counts to 0 and names to NULL
    int term = 0;
    
    while ( !feof(csv_file) ){
        next_field(csv_file, buffer, MAX_STRING_SIZE);
        term++;
        
       /* if(strcmp(hashTable[hashNumber]->name, name) == 0){ //if search name == name in bucket return 1
        
        *key = hashNumber; //set key/index to hashNumber
        value = 1;
    }
    else if(strcmp(hashTable[hashNumber]->name , "\0") == 0){ //if NULL in bucket return 0
        
        *key = hashNumber; //set key/index to hashNumber
        value = 0;
    }
    else{
        i = hashNumber;
        while(strcmp(hashTable[i]->name, "\0") != 0){ //while name isn't NULL value --- collisions -----
            
            i++; //increase hash by 1 and try again
            collisions++; //increase collision number by 1
            if(i == ARRAY_SIZE){ //if reached end of array, start at hashtable[0]
                i = 0;
            }
        }
        *key = i;
        value = 0;
    }*/
        if(search(buffer, &position)){ //if search = 1, increase count but dont replicate data
            hashTable[position]->count = hashTable[position]->count + 1; //increase count by 1
        }
        
        else{ //else, but name in new element
            createElement(buffer, position);
            
        }
    }
    fclose(csv_file); 
    float load = ((float)term / ARRAY_SIZE)*100;
    
    printf("Number of Collisions: %i\n", collisions);
    printf("Load in percent: %f\n", load);
    printf("Type stop to exit program.\n");
    
    
    while(strcmp(buffer, "stop") != 0){ // while word entered doesn't = stop
        printf("Enter name: ");
        scanf("%s", buffer); //add name to buffer array
        
        if(search(buffer, &position)){ //if search = 1, print count
            printf(">>>Name: %s\n>>>Count: %i\n", hashTable[position] -> name, hashTable[position]->count);
            
        }
        else if(strcmp(buffer, "stop") != 0){
            printf(">>>%s not found.\n", buffer); //else print not found
            
        }
    }
    
    return  0;
}