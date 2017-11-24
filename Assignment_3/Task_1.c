
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

typedef struct Tree_Node Tree_Node;

struct Tree_Node{
    char data;
    Tree_Node* left, right;
};

void tree_insert(Tree_Node* root, char data){
    Tree_Node* new_root = malloc(sizeof(Tree_Node));
    new_root -> data = data;
    new_root -> left = NULL;
    new_root -> right = NULL;



}

Tree_Node* tree_search(Tree_Node* root, char data){

}

void tree_print_sorted(Tree_Node* root){

}

void tree_delete(Tree_Node* root){

}





int  main ( int argc , char *argv[] ){


}