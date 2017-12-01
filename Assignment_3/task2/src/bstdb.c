#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.
#define Hash_size 10000000
typedef struct Books Books;

struct Books {
    int book_id;
    char *name;
    int word_count;
    Books *left;
    Books *right;
};

int nodes_search =0;
int words_searched =0;
int names_searched =0;
int collisions =0;
int count;
int add_count;
Books *root;

int i=0;

int bstdb_init ( void ) {
    if(1) {
        root = NULL;
        add_count = 0;
        count = 0;
        return 1;
    }
    else return 0;
    // This function will run once (and only once) when the database first
    // starts. Use it to allocate any memory you want to use or initialize
    // some globals if you need to. Function should return 1 if initialization
    // was successful and 0 if something went wrong.
    //	return 1;
}

Books * create_book(char *name, int word, int id) {
    Books *b = (Books*)malloc(sizeof(Books));
    b->book_id = id;
    b->name = name;
    b->word_count =word;
    b->left = NULL;
    b->right = NULL;
    return b;
}

int create_ID(char* s){  //djb2 algorithm uses 32
    int hash =0;
    while (*s) {
        hash = (32*( hash+ *s))% Hash_size; // hash * 33
        s++;
    }
    return hash;
}

/*
 Books* insert(Books* curr, char *name, int word_count, int id) {
 // printf("Got to insert function \n");
	if (curr == NULL){
 return create_book(name, word_count, id);
	}
	if (id < curr->book_id) {    //if its less than the root, move to the left
 // curr = curr->left;
 curr->left = insert(curr->left, name, word_count, id);
	}
	else if ( id >= curr->book_id) {   //if its greater than the root, move to the right
 //  curr = curr->right;
 curr->right = insert(curr->right, name, word_count, id);
	}
	return curr;
 
 }
 */

int bstdb_add ( char *name, int word_count ) {
    add_count++;
    int id = create_ID(name);
    //int id = id_gen();
    
    Books * new_book = create_book(name, word_count, id);
    if(root == NULL) {	//set root
        
        root = new_book;
        count++;
        return (root->book_id);
    }
    Books * curr = root;
    Books * prev = root;
    
    while (curr != NULL) {
        prev = curr;
        if (new_book->book_id > curr->book_id) {
            curr = curr->right;
        }
        else if (new_book->book_id == curr->book_id) {
            new_book->book_id++;
            collisions++;
        }
        else curr = curr->left;
    }
    
    if (new_book->book_id > prev->book_id) {
        prev->right = new_book;
        count++;
        return (prev->right->book_id);
    }
    else if (new_book->book_id < prev->book_id){
        prev->left = new_book;
        count++;
        return (prev->left->book_id);
    }
    else return -1;

}


Books* tree_search(Books* curr, int id) {
    if (id == curr->book_id) {   //if equal to root, print
        return curr;
    }
    else if(id < curr->book_id && curr->left != NULL) { //if less than root, move left
        nodes_search++;
        return tree_search(curr->left, id);
    }
    else if (id > curr->book_id && curr->right != NULL) { //if greater than root, move right
        nodes_search++;
        return tree_search(curr->right, id);
    }
    else { //cant find data
        return NULL;
    }
    
}


int bstdb_get_word_count ( int book_id ) {
    words_searched++;
    
    Books *book = (Books*)malloc(sizeof(Books));

    book = tree_search(root, book_id);
    
    if (book->book_id == book_id) {
        return (book->word_count);
    }
    else return -1;
    // This is a search function. It should traverse the binary search tree
    // and return the word_count of the node with the corresponding book_id.
    //
    // If the required node is not found, this function should return -1
}

char* bstdb_get_name ( int book_id ) {
    names_searched++;
    Books *book = (Books*)malloc(sizeof(Books));

    book = tree_search(root, book_id);
    if (book != NULL) {
        return (book->name);
    }
    else return NULL;
    // This is a search function. It should traverse the binary search tree
    // and return the name of the node with the corresponding book_id.
    //
    // If the required node is not found, this function should return NULL or 0
    
}

void print_sorted(Books * root) {
    if (root != NULL) {
        print_sorted(root->left);
        
        printf("%i \t %s \n", root->book_id, root->name);
        print_sorted(root->right);
    }
}

int max ( int a, int b) {
    if ( a >= b)
        return a;
    else return b;
}

int height (Books * curr) {
    if (curr == NULL)
        return 0;
    else {
        int h = 1 + max(height(curr->left), height(curr->right));
        return h;
    }
}
int left_h;
int right_h;
int Balanced(Books * curr) {
    if (curr == NULL){ //empty then balanced
        printf("This tree is empty \n");
        return 1;
    }
    else {
        left_h = height(curr->left);	//getting left height
        right_h = height(curr->right);	//getting right height
    }
    if (abs(left_h - right_h) <= 1 && Balanced(curr->left) && Balanced(curr->right))
        return 1;	//if balanced
    else return 0;	//not balanced
}

void bigNlil(Books * l) {
    Books *r = (Books*)malloc(sizeof(Books));
    r = root;
    if (r != NULL){ //empty then balanced
        while(l->left != NULL) {
            l = l->left;
        }
        while(r->right != NULL) {
            r = r->left;
        }
        printf("left most id %i \n right most id %i \n", l->book_id, r->book_id);
    }

}

void bstdb_stat ( void ) {

    printf("Number of tree nodes added matches expected?  -> ");
    if (count == add_count)
        printf("Yes\n");
    else printf("Nope\n");
    
    //average number of nodes passed to get to the searched one
    double av_nodes_searched = (double)nodes_search/(words_searched + names_searched);
    printf("The Average number of nodes traversed  -> %lf \n", av_nodes_searched);
    
    //Collisions in creating id's
    printf("Number of collisions when generating id's  -> %i \n", collisions);
    
    //Testing if tree is balanced
    Books *curr = (Books*)malloc(sizeof(Books));
    curr = root;
    int b = Balanced(curr);
    
    printf("\nIs the Tree Balanced?  -> ");
    if (b==1) {
        printf("Yes!! \n");
        printf("Both sides have %i nodes\n", left_h);
    }
    else {
        printf("Nope \n");
        printf("The number of nodes on Left of the tree   -> %i \n", left_h);
        printf("The number of nodes on Right of the tree  -> %i \n",right_h);
    }
    printf("Root info %i %s %i \n", root->book_id, root->name, root->word_count);

    
    // Use this function to show off! It will be called once after the
    // profiler ends. The profiler checks for execution time and simple errors,
    // but you should use this function to demonstrate your own innovation.
    //
    // Suggestions for things you might want to demonstrate are given below,
    // but in general what you choose to show here is up to you. This function
    // counts for marks so make sure it does something interesting or useful.
    //
    //  + Check if your tree is balanced and print the result
    //
    //  + Does the number of nodes in the tree match the number you expect
    //    based on the number of insertions you performed?
    //
    //  + How many nodes on average did you need to traverse in order to find
    //    a search result? 
    //
    //  + Can you prove that there are no accidental duplicate document IDs
    //    in the tree?
}

void delete(Books* curr) {
    if (curr != NULL) {
        delete(curr->left);  //deletes left
        delete(curr->right); //deletes right
        free(curr);
    }
}

void bstdb_quit ( void ) {
    //Books *curr = (Books*)malloc(sizeof(Books));
    //curr = root;
    delete(root);
    
    // This function will run once (and only once) when the program ends. Use
    // it to free any memory you allocated in the course of operating the
    // database.
}
