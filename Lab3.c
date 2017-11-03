//
//  main.c
//  Lab3.c
//
//  Created by Sophie Hegarty on 12/10/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
    char data;
    Node* next;
};

void add_node(Node** list, char data){
    
    Node* new_node = malloc(sizeof(Node)); //create new node to add data
    if (new_node == NULL) {
        fputs("Error in malloc\n", stderr);
        exit(1);
    }
    
    new_node->data = data;
    new_node->next = *list;
    *list = new_node;
    
    
}

void print_list(Node* list){
    Node* current = list;
    
    while(current != NULL){
        printf("%c\n", current ->data);
        current = current->next;
        
    }
}

void remove_node(Node** list, char data){
    Node *prev = NULL;
    Node *current = *list;
    //for (Node *current = *list; current; ) {

    while(current != NULL){
        if (current->data == data) {
            Node *del_entry = current;
            current = current->next;
                
            if (prev) {
                    prev->next = current;
                    
            } else {
                *list  = current;
            }

            free(del_entry);
        } else {
            prev = current;
            current = current->next;
        }
    }
        
}


int main(int argc, const char * argv[]) {
    
    Node* head = NULL;
    head = malloc(sizeof(Node));
    //head->data = 'a';
    //head->next = NULL;
    
    //the following characters are added to the list, from the head
    add_node(&head, 'A');
    //print_list(head);
    add_node(&head, 'B');
    //print_list(head);
    add_node(&head, 'C');
    //print_list(head);
    add_node(&head, 'D');
    
    print_list(head);
    remove_node(&head, 'C');
    print_list(head);
    
    
    
    return 0;
}
