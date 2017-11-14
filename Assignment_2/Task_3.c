//
//  Task_3.c
//  Assignment_2
//
//  Created by Sophie Hegarty on 13/11/2017.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle

struct Game {
	int score, releaseYear;
	char title[MAX_BUFFER], platform[MAX_BUFFER];
};

// The CSV parser
int
next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

// Stuff to make life a bit neater in main
void fetch_game( FILE *csv, struct Game *g ) {
	char buf[MAX_BUFFER];

    next_field( csv, g->title, MAX_BUFFER );  // name and type are just strings so read
    next_field( csv, g->platform, MAX_BUFFER );  // name and type are just strings so read
	next_field( csv, buf, MAX_BUFFER );      // load id into buffer as string
	g->score = atoi(buf);                       // then parse to integer
    next_field( csv, buf, MAX_BUFFER );      // load id into buffer as string
	g->releaseYear = atoi(buf);   

}

void print_game( struct Game *g ) {
	printf("  %s %s %i %i\n", g->title, g->platform, g->score, g->releaseYear );

}

int
main ( int argc, char *argv[] ) {
	FILE *f;		
	struct Game g;
    f = fopen("truncated.csv", "r");


	//fetch_game( f, &g ); // discard the header data in the first line

	// Now read and print pokemon until the end of the file
	while(!feof(f)) {
		fetch_game( f, &g );
		print_game( &g );
		printf("\n");
	}

	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}
