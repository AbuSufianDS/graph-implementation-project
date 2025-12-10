#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
    int inDegree; 
} AdjList;

typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);

Queue* createQueue(unsigned capacity);
bool isQueueEmpty(Queue* queue);
bool isQueueFull(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);
int front(Queue* queue);

void topologicalSortMatrix(int matrix[][7], int vertices);
void topologicalSortList(Graph* graph);

Graph* buildGraphFromMatrix(int matrix[][7], int vertices);

#endif