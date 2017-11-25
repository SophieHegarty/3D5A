
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

void tree_insert(Tree_Node** root, char data){
    Tree_node *temp = NULL;
    
    if(!(*root)) {
        temp = (Tree_node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *root = temp;
        return;
    }

    if(val < (*root)->data) {
        insert(&(*root)->left, val);
     } 
     else if(val > (*root)->data) {
        insert(&(*root)->right, val);
      }
    
}

Tree_Node* tree_search(Tree_Node** root, char data){
    if(!(*root)) {
        return NULL;
    }
    
   if(val == (*root)->data) {
        return *root;
   } 
   else if(val < (*root)->data) {
        search(&((*root)->left), val);
   } 
   else if(val > (*root)->data){
        search(&((*root)->right), val);
  }
 
}

void tree_print_sorted(Tree_Node* root){

}

void tree_delete(Tree_Node* root){
    if (root) {
       deltree(root->left);
       deltree(root->right);
       free(root);
  }
}





int  main ( int argc , char *argv[] ){


}
