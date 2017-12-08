/*                                                                             
 * ============================================================================
 *                                                                             
 *       Filename:  graph.c                                                    
 *                                                                             
 *    Description:  This file demonstrates an extremely naive, limited method
 *                  of implementing a graph structure in C. It does a few 
 *                  things well which you should pay attention to:
 * 
 *                  + Any dynamic memory allocation (malloc or calloc) is 
 *                    tested for failure immediately after the call is made
 *                  + It follows an object oriented programming style with
 *                    functions that perform operations on structs. It's not
 *                    OOP, but if you turn your head and squint, it could be
 *                  + It uses no globals
 *                  + It has a clear, distinct sequence of initialize, run and
 *                    shutdown stages
 *                  + During shutdown we release any and all dynamically
 *                    allocated memory (you can test for leaks using valgrind)
 *                  + Does a lot of error checking
 * 
 *                  It does a few things extremely badly which you should fix:
 *  
 *                  + Getting a vertex from the graph is slow
 *                  + Graph needs to know how big it is expected to get (needs
 *                    a max_vertices attribute). Shouldn't it grow naturally 
 *                    with the size of the input?
 *                  + Can't handle any sort of complex string labels
 *                  + Vertices can only store a (very) limited number of edges
 *                  + No method of weighting edges
 *                  + Following an edge to get to the next vertex requires a
 *                    call to graph_get_vertex. Couldn't edges just store
 *                    pointers to vertices instead?
 *                  + It has no functionality for removing/deleting edges
 *                  + Anything which fails will do so silently. Hard to track
 *                    down any errors
 *                                                                             
 *        Version:  1.0                                                        
 *        Created:  04/12/17                                          
 *       Revision:  none                                                       
 *       Compiler:  clang                                                      
 *                                                                             
 *         Author:  Gary Munnelly (gm), munnellg@tcd.ie                        
 *        Company:  Adapt Centre, Trinity College Dublin                       
 *                                                                             
 * ============================================================================
 */
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// Max number of edges a node can have (shouldn't need this)
#define MAX_EDGES    8 
struct vertex {
    char id;
    
    // An array is very rigid. How do we make this better?
    // How do we handle the case where edges have weights?
    // Maybe it's time for another struct?
    char edges[MAX_EDGES];
    int num_edges;
    struct vertex* next;
};

struct graph {
    int max_vertices;        // Maximum size of the graph. Do we need a limit?
    int num_vertices;        // current size of the graph
    struct vertex *vertices; // pointer to all nodes in the graph
    int *visited; //addded new
    struct vertex** adjLists; //added new
};

struct queue {
    int items[MAX_EDGES];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int v);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

// Functions which manipulate vertices. 

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

void bfs(struct graph* graph, int startVertex) {

    struct queue* q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    while(!isEmpty(q)){
        printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
    
       struct vertex* temp = graph->adjLists[currentVertex];
    
       while(temp) {
            int adjVertex = temp->num_edges;

            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}
 
struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


int isEmpty(struct queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(struct queue* q, int value){
    if(q->rear == MAX_EDGES-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }    
}

struct vertex* vertex_new      ( char id );
int            vertex_init     ( struct vertex *v, char id );
int            vertex_add_edge ( struct vertex *v, char id );
void           vertex_print    ( struct vertex *v );
void           vertex_free     ( struct vertex *v );

// Functions which manipulate the graph

struct graph*  graph_new        ( int max_vertices );
int            graph_init       ( struct graph *g, int max_vertices );
struct vertex* graph_get_vertex ( struct graph *g, char id );
int            graph_add_vertex ( struct graph *g, char id );
int            graph_add_edge   ( struct graph *g, char id1, char id2 );
void           graph_print      ( struct graph *g );
void           graph_free       ( struct graph *g );


int
main(int argc, char *argv[]) {

    struct graph *graph;
    
    // Initialization
    graph = graph_new( 7 );
    if (!graph) { return EXIT_FAILURE; }

    // Could load this from a file, but we'll hard code it for demo purposes
    for ( char c='A'; c<='F'; c++ ) {
        graph_add_vertex( graph, c );
    }

    for ( char c='A'; c<='F'; c++ ) {
        graph_add_vertex( graph, c );
    }

    graph_add_edge ( graph, 'A', 'B' );
    graph_add_edge ( graph, 'A', 'D' );
    graph_add_edge ( graph, 'A', 'E' );

    graph_add_edge ( graph, 'B', 'C' );
    graph_add_edge ( graph, 'B', 'D' );
    
    graph_add_edge ( graph, 'C', 'D' );
    graph_add_edge ( graph, 'C', 'B' );

    graph_add_edge ( graph, 'D', 'F' );

    graph_add_edge ( graph, 'E', 'D' );

    graph_add_edge ( graph, 'F', 'C' );

    // Do stuff
    graph_print(graph);
    bfs(graph,0);
    // terminate
    graph_free(graph);

    return EXIT_SUCCESS;
}

struct vertex*
vertex_new ( char id ) {
    struct vertex *v;

    // I did not test malloc here because I know that vertex_init will do it
    // for me. If there is an issue with the allocation then vertex_init will
    // return 0
    v = malloc ( sizeof(struct vertex) );
    if(!vertex_init(v, id)) {
        // On failure, just to be safe, free whatever got allocated
        vertex_free(v);
        v = NULL;
    }
    return v;
}

int
vertex_init ( struct vertex *v, char id ) {
    // Check that we have a vertex before we do anything
    if ( v == NULL ) { return 0; }

    // Initialize everything
    v->id = id;
    v->num_edges = 0;

    // return successful initialization
    return 1;
}

void
vertex_print ( struct vertex *v ) {
    // Check that we have a vertex before we do anything
    if (!v) { return; }

    // Print vertex label
    printf("%c", v->id);
   
    // Print vertex edges
    for ( int i=0; i<v->num_edges; i++ ) {
        printf(" -> %c", v->edges[i]);
    }

    printf("\n");
}

void
vertex_free ( struct vertex *v ) {
    if (v) { free(v); }
}

int
vertex_add_edge ( struct vertex *v, char id ) {
    if ( !v ) { return 0; }

    // Check to see that we haven't reached max capacity of edges
    if ( v->num_edges >= MAX_EDGES ) { return 0; }

    // If we have room, store the edge and update this vertex's edge count
    v->edges[v->num_edges] = id;
    v->num_edges++;

    return 1;
}

struct graph *
graph_new ( int max_vertices ) {
    struct graph *g;

    // I did not test malloc here because I know that graph_init will do it
    // for me. If there is an issue with the allocation then graph_init will
    // return 0
    g = malloc(sizeof(struct graph));
    if (!graph_init ( g, max_vertices )) {
        // On failure, just to be safe, free whatever got allocated
        graph_free(g);
        g = NULL;
    }

    // g will point to a new graph on success or NULL on failure
    return g;
}

int
graph_init ( struct graph *g, int max_vertices ) {
    // Good idea to make sure that g actually points to something
    if (!g) { return 0; };

    // Set everything up
    g->max_vertices = max_vertices;
    g->num_vertices = 0;
    // Try to malloc out some space for the vertices
    g->vertices = malloc(sizeof(struct vertex) * g->max_vertices);
    // if malloc fails then this function should report failure
    if(g->vertices == NULL) { return 0; }

    // return success
    return 1;
}

struct vertex *
graph_get_vertex ( struct graph *g, char id ) {
    // Good idea to make sure that g actually points to something
    if (!g) { return NULL; }

    // This linear search to find a vertex is horrible!
    // What datastructures can we use to make it faster?
    struct vertex *v = NULL;
    for ( int i=0; i<g->num_vertices; i++ ) {
        if ( g->vertices[i].id == id ) {
            v = &g->vertices[i];
            break;
        }
    }

    // v will point to the vertex if we found it. Else it will be NULL
    return v;
}

int
graph_add_vertex ( struct graph *g, char id ) {
    // First make sure that we've been given a graph to operate on
    if (!g) { return 0; }
    // Make sure the graph is not full
    if (g->num_vertices >= g->max_vertices) { return 0; }

    // Check to see if the vertex is already in the graph    
    struct vertex *v = graph_get_vertex(g, id);
    // If it is, report failure
    if (v) { return 0; }

    // Now try to add the vertex to the graph.    
    if (!vertex_init( &g->vertices[g->num_vertices], id )) { 
        return 0;
    }

    // If init was successful then increase the vertices count
    g->num_vertices++;

    // return success
    return 1;
}

int
graph_add_edge ( struct graph *g, char id1, char id2 ) {
    // First make sure that we've been given a graph to operate on
    if (!g) { return 0; }

    // Ensure both vertices are actually in the graph
    struct vertex *v1 = graph_get_vertex(g, id1);
    struct vertex *v2 = graph_get_vertex(g, id2);
    if (!v1 || !v2) { return 0; }

    // return the result of the vertex_add_edge function (1 if edge added, 0
    // if there was a problem)
    return vertex_add_edge( v1, v2->id );;
}

void
graph_print ( struct graph *g ) {
    if (!g) { return; }

    // Iterate over all vertices in the graph and print them
    for ( int i=0; i<g->num_vertices; i++ ) {
        vertex_print( &g->vertices[i] );
    }
}

void
graph_free ( struct graph *g ) {
    // Do some checks and free whetever needs to be freed
    if (g) {
        if (g->vertices) { free(g->vertices); }
        free(g);
    }
}
