
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

#define ARRAY_SIZE 29

struct  Tree_Node;
struct  Tree_Node{
    char data;
    struct Tree_Node *left, *right;
};

void tree_insert(struct Tree_Node** root, char data){
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
    
}

struct Tree_Node* tree_search(struct Tree_Node** root, char data){
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
}

void tree_print_sorted(struct Tree_Node* root){
    if (root)
    {
        print_postorder(root->left);
        print_postorder(root->right);
        printf("%d\n",root->data);
    }

}

void tree_delete(struct Tree_Node* root){
    if (root) {
       tree_delete(root->left);
       tree_delete(root->right);
       free(root);
  }
}





int  main ( int argc , char *argv[] ){

    struct Tree_Node *ptr = NULL;
    char array[ARRAY_SIZE] = {'F', 'L', 'O', 'C', 'C', 
'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I', 'H', 'I', 'L', 'I', 'P', 'I', 'L','I', 'F', 'I', 'C', 'A', 'T', 'I', 'O', 'N'};

    for(int i = 0; i <29; i++){
        tree_insert(ptr*, i);
    }
    



}




/*int vektor[10];    
int random;
int uniqueflag;
int i, j

for(i = 0; i < 10; i++) {
     do {

        uniqueflag = 1;
        random = rand() % 100+ 1;

        for (j = 0; j < i && uniqueflag == 1; j++) {
           if (vektor[j] == random) {
              uniqueflag = 0;
           }
        }
     } while (uniqueflag != 1);
     vektor[i] = random;
}*/
