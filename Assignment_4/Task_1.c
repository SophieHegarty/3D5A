#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 6

struct Vertex {
    char label;
    bool visited;
};

int stack[MAX];
int top = -1;

//array of vertices
struct Vertex* lstVertices[MAX];

//adjacency matrix
int adjMatrix[MAX][MAX];

//stack functions

void push(int item) {
    stack[++top] = item;
}

int pop() {
    return stack[top--];
}

int peek() {
    return stack[top];
}

bool isStackEmpty() {
    return top == -1;
}


//queue variables

int queue[MAX];
int rear = -1;
int front = 0;
int queueItemCount = 0;

//graph variables

//array of vertices
struct Vertex* lstVertices[MAX];

//adjacency matrix
int adjMatrix[MAX][MAX];

//vertex count
int vertexCount = 0;


//queue functions

void insert(int data) {
    queue[++rear] = data;
    queueItemCount++;
}

int removeData() {
    queueItemCount--;
    return queue[front++];
}

bool isQueueEmpty() {
    return queueItemCount == 0;
}

//graph functions

//add vertex to the vertex list
void addVertex(char label) {
    struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->label = label;
    vertex->visited = false;
    lstVertices[vertexCount++] = vertex;
}

//add edge to edge array
void addEdge(int start,int end) {
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1;
}

//display the vertex
void displayVertex(int vertexIndex) {
    printf("%c ",lstVertices[vertexIndex]->label);
}

//get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex) {
    int i;
    
    for(i = 0; i<vertexCount; i++) {
        if(adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false)
            return i;
    }
    
    return -1;
}

void breadthFirstSearch() {
    int i;
    
    //mark first node as visited
    lstVertices[0]->visited = true;
    
    //display the vertex
    displayVertex(0);
    
    //insert vertex index in queue
    insert(0);
    int unvisitedVertex;
    
    while(!isQueueEmpty()) {
        //get the unvisited vertex of vertex which is at front of the queue
        int tempVertex = removeData();
        
        //no adjacent vertex found
        while((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1) {
            lstVertices[unvisitedVertex]->visited = true;
            displayVertex(unvisitedVertex);
            insert(unvisitedVertex);
        }
        
    }
    
    //queue is empty, search is complete, reset the visited flag
    for(i = 0;i<vertexCount;i++) {
        lstVertices[i]->visited = false;
    }    
}


//graph functions
void depthFirstSearch() {
   int i;

   //mark first node as visited
   lstVertices[0]->visited = true;

   //display the vertex
   displayVertex(0);   

   //push vertex index in stack
   push(0);

   while(!isStackEmpty()) {
      //get the unvisited vertex of vertex which is at top of the stack
      int unvisitedVertex = getAdjUnvisitedVertex(peek());

      //no adjacent vertex found
      if(unvisitedVertex == -1) {
         pop();
      } else {
         lstVertices[unvisitedVertex]->visited = true;
         displayVertex(unvisitedVertex);
         push(unvisitedVertex);
      }
   }

   //stack is empty, search is complete, reset the visited flag        
   for(i = 0;i < vertexCount;i++) {
      lstVertices[i]->visited = false;
   }        
}



int main() {
   int i, j;

    for(i = 0; i<MAX; i++){ // set adjacency {
      for(j = 0; j<MAX; j++) // matrix to 0
         adjMatrix[i][j] = 0;
   }
   
   addVertex('A');   // 0
   addVertex('B');   // 1
   addVertex('C');   // 2
   addVertex('D');   // 3
   addVertex('E');   // 4
   addVertex('F');   //5
 
   addEdge(0, 1);    // A - B
   addEdge(0, 3);    // A - B
   addEdge(0, 4);    // S - C
    
   addEdge(1, 2);    // A - D
   addEdge(1, 3);    // B - D
    
   addEdge(2, 1);    // C - D
    addEdge(2, 3);    // C - D
    
    addEdge(3, 5);    // C - D
    
    addEdge(4, 3);    // C - D
    
    addEdge(5, 2);    // C - D
    

   printf("Depth First Search: ");

   depthFirstSearch(); 
    printf("\nBreadth First Search: ");
    
    breadthFirstSearch();

   return 0;   
}

