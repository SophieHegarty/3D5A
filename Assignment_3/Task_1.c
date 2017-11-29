
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

struct Tree_Node* tree_insert(struct Tree_Node *root, int data) {
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

struct node* search(struct node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;
    
    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}

void tree_print_sorted(struct Tree_Node* root){
    if (root)
    {
        tree_print_sorted(root->left);
        tree_print_sorted(root->right);
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

    struct Tree_Node *root = NULL;
    char* data = "FLOCCINAUCINIHILIPILIFICATION";

    for(int i = 0; i <ARRAY_SIZE - 1; i++){
        root = tree_insert(root, data[i]);
    }

    tree_print_sorted(root);
    
}



//https://gist.github.com/aaronjwood/2780f31768691b1d69ed
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
