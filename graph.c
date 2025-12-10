#include "graph.h"
#include <limits.h>

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
        graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));
    
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
        graph->array[i].inDegree = 0;
    }
    
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
        graph->array[dest].inDegree++;
}

void printGraph(Graph* graph) {
    printf("\nGraph Representation (Adjacency List):\n");
    printf("======================================\n");
    
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* current = graph->array[v].head;
        
        printf("Vertex %d (in-degree: %d): ", v, graph->array[v].inDegree);
        
        if (current == NULL) {
            printf("No outgoing edges");
        } else {
            while (current != NULL) {
                printf("-> %d ", current->dest);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

Graph* buildGraphFromMatrix(int matrix[][7], int vertices) {
    Graph* graph = createGraph(vertices);
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
    
    return graph;
}

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

bool isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(Queue* queue) {
    if (isQueueEmpty(queue)) return INT_MIN;
    return queue->array[queue->front];
}

void topologicalSortMatrix(int matrix[][7], int vertices) {
    printf("\nTopological Sort (Adjacency Matrix):\n");
    printf("====================================\n");
    
    int inDegree[vertices];
    for (int i = 0; i < vertices; i++) {
        inDegree[i] = 0;
        for (int j = 0; j < vertices; j++) {
            inDegree[i] += matrix[j][i];
        }
    }
    
    Queue* queue = createQueue(vertices);
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    int count = 0;
    int topologicalOrder[vertices];

        while (!isQueueEmpty(queue)) {
        int u = dequeue(queue);
        topologicalOrder[count++] = u;
        
        for (int v = 0; v < vertices; v++) {
            if (matrix[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    enqueue(queue, v);
                }
            }
        }
    }
    
    if (count != vertices) {
        printf("Graph contains a cycle! Cannot perform topological sort.\n");
        free(queue->array);
        free(queue);
        return;
    }
        printf("Topological Order: ");
    for (int i = 0; i < vertices; i++) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
    
    free(queue->array);
    free(queue);
}

void topologicalSortList(Graph* graph) {
    printf("\nTopological Sort (Adjacency List):\n");
    printf("==================================\n");
    
    int vertices = graph->numVertices;
    
    int* inDegree = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        inDegree[i] = graph->array[i].inDegree;
    }
    
    Queue* queue = createQueue(vertices);
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    int count = 0;
    int topologicalOrder[vertices];
    
    while (!isQueueEmpty(queue)) {
        int u = dequeue(queue);
        topologicalOrder[count++] = u;
        
        AdjListNode* current = graph->array[u].head;
        while (current != NULL) {
            int v = current->dest;
            inDegree[v]--;
            if (inDegree[v] == 0) {
                enqueue(queue, v);
            }
            current = current->next;
        }
    }
    
    if (count != vertices) {
        printf("Graph contains a cycle! Cannot perform topological sort.\n");
        free(inDegree);
        free(queue->array);
        free(queue);
        return;
    }
    
    printf("Topological Order: ");
    for (int i = 0; i < vertices; i++) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
    
    free(inDegree);
    free(queue->array);
    free(queue);
}