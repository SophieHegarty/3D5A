//
//  main.c
//  Lab0
//
//  Created by Sophie Hegarty on 01/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int next_field(FILE *csv, char *buffer, int max_length){
    char current = fgetc(csv);  //get character from the csv file, set as current character
    int i = 0;
    int value;
    
    while(current != EOF && current != ',' && current != '\n' ){
        buffer[i] = current;
        current = fgetc(csv);
        i++;
    }
    
    if(current == ','){    //if curretn character = , then but 0 in buffer and return 0
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

    FILE *csv_file;
    csv_file = fopen("/Users/sophiehegarty/Documents/Trinity Engineering/TCD JS/Lab0/Lab0/pokemon(1).csv", "r");  //read in csv file
    char data[1024];     //array storing data
    char *buffer = data;
    int new_record = -1;          //variable storing state of return from function, initailised as a non-return number
    int count = 0;      //count how many pokemon in file
    
    
    if(csv_file == NULL){   //error checking for file reading
        printf("No File Read In.\n");
    };
    
    while(!feof(csv_file)){     //while the file isnt at the end, put return value into j
        //printf("Inside while loop");
        new_record = next_field(csv_file, buffer, 1024);
        //printf("buffer %d", new_record);
        
        if(new_record == 0){     //if return = 0 then take new line for new field
            printf("%s\n", buffer);
        }
        else if(new_record == 1){        //if return = 1 then take 2 new line for new record
            printf("%s\n\n", buffer);
            count++;
        }
    }

        puts("End-of-File reached.");
        printf ("Total number of records read: %d\n", count);
    fclose(csv_file);

    
    return 0;

};
