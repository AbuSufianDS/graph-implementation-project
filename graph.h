#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

// Structure for adjacency list node
typedef struct AdjListNode {
    int dest;
    float weight;  // For Dijkstra algorithm
    struct AdjListNode* next;
} AdjListNode;

// Structure for adjacency list
typedef struct AdjList {
    AdjListNode* head;
    int inDegree; // For topological sort
} AdjList;

// Structure for graph
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// Queue structure for topological sort
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// Graph creation and manipulation
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, float weight);
void printGraph(Graph* graph);
void printFigure920Graph(Graph* graph);

// Queue operations
Queue* createQueue(unsigned capacity);
bool isQueueEmpty(Queue* queue);
bool isQueueFull(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);
int front(Queue* queue);

// Topological sort functions
void topologicalSortMatrix(int matrix[][7], int vertices);
void topologicalSortList(Graph* graph);

// Helper function to build graph from matrix
Graph* buildGraphFromMatrix(int matrix[][7], int vertices);

// Dijkstra algorithm
void dijkstra(Graph* graph, int src);

// Function to create Figure 9.20 graph
Graph* createFigure920Graph();

#endif
