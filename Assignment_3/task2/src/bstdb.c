#include "bstdb.h"
#include <stddef.h>
#include <stdio.h>

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
#define TITLE_SIZE 256

typedef struct Books Books;
struct Books {
	char title[TITLE_SIZE];
	int word_count;
	int bookID;
	Books *left, *right;

};



int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	Books* root = NULL;

	return 1;
}

void create_Node(Books* root){
	if (root == NULL) {
        root = (struct Books*)malloc(sizeof(struct Books));
	}
	if (root == NULL) {
        printf("Error in malloc\n");
        exit(1);
    }
}

int create_bookID(char* name){
 int hash = 0;
    while(*name)
    {
        hash = (hash + *name) % TITLE_SIZE;
        name++;
    }
    return hash;
}

int doublehash(char* name, int bookId){
	int hash = bookId; //modulous a prime number
    while(*name)
    {
        hash = ((hash + *name) *31) % TITLE_SIZE;
        name++;
    }
    return hash;
}



int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	root = create_Node(root);
	int bookID = create_bookID(name);
	int check = -1;

	
	while(check != 1){
		bookID = doublehash(name, bookID);
		check = duplicate(name, bookID);
	}

	if (root == NULL) {
			root = (struct Books *)malloc(sizeof(struct Books));
			root-> Books.title[]= title;
			root -> Books.word_count = word_count;
			root -> Books.bookID = bookID;
			root->left = NULL;
			root->right = NULL;
			return bookID;
		} else if (Books.bookID < root->bookID) {
			root->left = bstdb_add(root->left, bookID);
			return bookID;
		} else {
			root->right = bstdb_add(root->right, bookID);
			return bookID;
		}

	return -1;
}

int duplicates(Books* root, int bookID){
	int check = -1;

	while(root ->bookID != bookID ){
		if (root == NULL || root->bookID == bookID)
			check = 1;
			break;
		// Key is greater than root's key
		else if (root->bookID < bookID){
			check = 1;
		} else{
		// Key is smaller than root's key
			check = 1;
		}
		check = 0;
	}
	return check;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	return 0;
}

void
bstdb_stat ( void ) {
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

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	  if (root) {
        tree_delete(root->left);
        tree_delete(root->right);
        free(root
}
