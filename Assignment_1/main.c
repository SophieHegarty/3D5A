//
//  main.c
//  Lab0
//
//  Created by Sophie Hegarty on 01/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 99991  //best be prime

typedef struct Element Element;
struct Element{
    char name[MAX_STRING_SIZE];
    int count;
};

Element hashTable[ARRAY_SIZE];

/*void initialise_hash(Element* hashtable){
 for(int i = 0; i < ARRAY_SIZE ; i++){
 hashTable[i] = 0;
 }
 }*/


int hash_function(char* s){
    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    return hash;
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


int main(int argc, const char * argv[]) {

    FILE* csv_file;
    csv_file = fopen("/users/ugrad/hegartso/Documents/Assignment_1/names.csv", "r");  //read in csv file
    char data[1024];     //array storing data
    char *buffer = data;
    int new_record = -1;          //variable storing state of return from function, initailised as a non-return number
    int count = 0;      //count how many pokemon in file
    int hashNumber =0;
    
    printf("File Read In.\n");
    if(csv_file == NULL){   //error checking for file reading
        printf("No File Read In.\n");
    };
    
    while(!feof(csv_file)){     //while the file isnt at the end, put return value into j
        //printf("Inside while loop");
        new_record = next_field(csv_file, buffer, 1024);
        hashNumber = hash_function(buffer);
        printf("%s\n", hashNumber);
        
        if(new_record == 0){     //if return = 0 then take new line for new field
            printf("%s\n", buffer);
            hashTable[hashNumber] = scy
        }
        else if(new_record == 1){        //if return = 1 then take 2 new line for new record
            printf("%s\n\n", buffer);
            count++;
        }
    }

        puts("End-of-File reached.");
    fclose(csv_file);

    
    return 0;

};