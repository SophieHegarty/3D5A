
//
//  Task_1.c
//  Assignment_3
//
//  Created by Sophie Hegarty on 19/11/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define ARRAY_SIZE 29

struct  Tree_Node;
struct  Tree_Node{
    char data;
    struct Tree_Node *left, *right;
};

/*void tree_insert(struct Tree_Node** root, char data){
 struct Tree_Node *temp = NULL;
 
 if(!(*root)) {
 temp = (struct Tree_Node *)malloc(sizeof(struct Tree_Node));
 temp->left = temp->right = NULL;
 temp->data = data;
 *root = temp;
 return;
 }
 
 if(data < (*root)->data) {
 tree_insert(&(*root)->left, data);
 }
 else if(data > (*root)->data) {
 tree_insert(&(*root)->right, data);
 }
 
 }*/

struct Tree_Node* tree_insert(struct Tree_Node *root, char data) {
    if (root == NULL) {
        root = (struct Tree_Node *)malloc(sizeof(struct Tree_Node));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    } else if (data < root->data) {
        root->left = tree_insert(root->left, data);
    } else {
        root->right = tree_insert(root->right, data);
    }
    
    return root;
}

/*struct Tree_Node* tree_search(struct Tree_Node** root, char data){
 if(!(*root))
 {
 return NULL;
 }
 
 if(data < (*root)->data)
 {
 tree_search(&((*root)->left), data);
 }
 else if(data > (*root)->data)
 {
 tree_search(&((*root)->right), data);
 }
 else if(data == (*root)->data)
 {
 return *root;
 }
 }*/

struct Tree_Node* tree_search(struct Tree_Node* root, char data)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->data == data)
        return root;
    
    // Key is greater than root's key
    if (root->data < data)
        return tree_search(root->right, data);
    
    // Key is smaller than root's key
    return tree_search(root->left, data);
}

void tree_print_sorted(struct Tree_Node* root){
    if (root)
    {
        tree_print_sorted(root->left);
        printf("%c\n",root->data);
        tree_print_sorted(root->right);
    }
    
}

void tree_delete(struct Tree_Node* root){
    if (root) {
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
}


int search_control(struct Tree_Node* root, char search){
    int x = -1;
    if(tree_search(root, search) == NULL){
        x = 0;
        //printf("INSIDE NULL ROOT");
    }
    else{
        //printf("INSIDE ROOT ROOT");
        x = 1;
    }
    return x;
}


int  main ( int argc , char *argv[] ){
    
    struct Tree_Node *root = NULL;
    
    char *data[ARRAY_SIZE] = {"F","L","O","C","C","I","N","A","U","C","I","N","I","H","I","L","I","P","I","L","I","F","I","C","A","T","I","O","N"};
    
    for(int i = 0; i <ARRAY_SIZE - 1; i++){
        printf("%c", *data[i]);
        root = tree_insert(root, *data[i]);
    }

    time_t t;

    srand((unsigned) time(&t));
    
    tree_print_sorted(root);
    char randomletter = 'A' + (rand() % 26);
    //char letter = 'C';
    int searching = search_control(root, randomletter);
    
    if(searching == 0){
        printf("%c Not Found in Tree\n", randomletter);
    }
    else if(searching == 1){
        printf("%c Found in Tree\n", randomletter);
    }
    
   char randomletter_2 = 'Z' - (random() % 26);;
    searching = search_control(root, randomletter_2);
    
    if(searching == 0){
        printf("%c Not Found in Tree\n",randomletter_2);
    }
    else if(searching == 1){
        printf("%c Found in Tree\n", randomletter_2);
    }
    
        
    tree_delete(root);
        
    
    return 0;
}

