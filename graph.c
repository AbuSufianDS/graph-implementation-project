#include "graph.h"
#include <math.h>

// Create a new adjacency list node
AdjListNode* newAdjListNode(int dest, float weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a graph of given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    // Create array of adjacency lists
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
        graph->array[i].inDegree = 0;
    }
    
    return graph;
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest, float weight) {
    // Add edge from src to dest
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Increase in-degree of destination vertex
    graph->array[dest].inDegree++;
}

// Print the graph
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
                printf("-> %d(%.2f) ", current->dest, current->weight);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Build graph from adjacency matrix (for Figure 9.1)
Graph* buildGraphFromMatrix(int matrix[][7], int vertices) {
    Graph* graph = createGraph(vertices);
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j, 1.0); // Default weight 1.0
            }
        }
    }
    
    return graph;
}

// Queue Implementation for Topological Sort

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
    return (queue->size == (int)queue->capacity);
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

// Topological Sort using Adjacency Matrix
void topologicalSortMatrix(int matrix[][7], int vertices) {
    printf("\nTopological Sort (Adjacency Matrix):\n");
    printf("====================================\n");
    
    // Calculate in-degrees
    int inDegree[vertices];
    for (int i = 0; i < vertices; i++) {
        inDegree[i] = 0;
        for (int j = 0; j < vertices; j++) {
            inDegree[i] += matrix[j][i];
        }
    }
    
    // Create queue and enqueue vertices with in-degree 0
    Queue* queue = createQueue(vertices);
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    // Count of visited vertices
    int count = 0;
    int topologicalOrder[vertices];
    
    // Process queue
    while (!isQueueEmpty(queue)) {
        int u = dequeue(queue);
        topologicalOrder[count++] = u;
        
        // Reduce in-degree of adjacent vertices
        for (int v = 0; v < vertices; v++) {
            if (matrix[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    enqueue(queue, v);
                }
            }
        }
    }
    
    // Check for cycle
    if (count != vertices) {
        printf("Graph contains a cycle! Cannot perform topological sort.\n");
        free(queue->array);
        free(queue);
        return;
    }
    
    // Print topological order
    printf("Topological Order: ");
    for (int i = 0; i < vertices; i++) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
    
    free(queue->array);
    free(queue);
}

// Topological Sort using Adjacency List
void topologicalSortList(Graph* graph) {
    printf("\nTopological Sort (Adjacency List):\n");
    printf("==================================\n");
    
    int vertices = graph->numVertices;
    
    // Make a copy of in-degrees
    int* inDegree = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        inDegree[i] = graph->array[i].inDegree;
    }
    
    // Create queue and enqueue vertices with in-degree 0
    Queue* queue = createQueue(vertices);
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    // Count of visited vertices
    int count = 0;
    int topologicalOrder[vertices];
    
    // Process queue
    while (!isQueueEmpty(queue)) {
        int u = dequeue(queue);
        topologicalOrder[count++] = u;
        
        // Reduce in-degree of adjacent vertices
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
    
    // Check for cycle
    if (count != vertices) {
        printf("Graph contains a cycle! Cannot perform topological sort.\n");
        free(inDegree);
        free(queue->array);
        free(queue);
        return;
    }
    
    // Print topological order
    printf("Topological Order: ");
    for (int i = 0; i < vertices; i++) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
    
    free(inDegree);
    free(queue->array);
    free(queue);
}

// ================= DIJKSTRA ALGORITHM =================

// Dijkstra's algorithm - simplified version
void dijkstra(Graph* graph, int src) {
    int V = graph->numVertices;
    float dist[V];
    int visited[V];
    int parent[V];
    
    // Initialize
    for (int i = 0; i < V; i++) {
        dist[i] = FLT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    // Distance of source from itself is 0
    dist[src] = 0;
    
    printf("\nDijkstra algorithm (source vertex %d):\n", src);
    printf("0\n");  // Initial output as per example
    
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Find the vertex with minimum distance
        float min = FLT_MAX;
        int u = -1;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        // Update dist value of adjacent vertices
        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            float weight = pCrawl->weight;
            
            if (!visited[v] && dist[u] != FLT_MAX && 
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            pCrawl = pCrawl->next;
        }
        
        // Print intermediate results as per example format
        printf("0 ");
        for (int v = 0; v < V; v++) {
            if (v != src && dist[v] < FLT_MAX && visited[v]) {
                // Build path
                if (parent[v] != src && parent[v] != -1) {
                    printf("to %d distance: %.2f  ", parent[v] + 1, dist[parent[v]]);
                }
                printf("to %d distance: %.2f  ", v + 1, dist[v]);
            }
        }
        printf("\n");
    }
    
    // Print final distances
    printf("\nFinal shortest distances from vertex %d:\n", src + 1);
    for (int i = 0; i < V; i++) {
        if (i != src && dist[i] < FLT_MAX) {
            printf("Vertex %d: distance = %.2f, path: ", i + 1, dist[i]);
            
            // Print path
            int path[V];
            int path_len = 0;
            int current = i;
            
            while (current != -1) {
                path[path_len++] = current + 1;  // Convert to 1-based
                current = parent[current];
            }
            
            // Print path in reverse
            for (int j = path_len - 1; j >= 0; j--) {
                printf("%d", path[j]);
                if (j > 0) printf(" -> ");
            }
            printf("\n");
        } else if (i != src) {
            printf("Vertex %d: unreachable\n", i + 1);
        }
    }
}

// Function to create Figure 9.20 graph
Graph* createFigure920Graph() {
    // Note: Vertices are 1-7 in problem, but we'll use 0-6 internally
    Graph* graph = createGraph(7);
    
    // Add edges as per Figure 9.20
    // Convert from 1-based to 0-based indexing
    // (1,2,2), (1,4,1), (2,5,10), (2,4,3), (3,6,5),
    // (4,3,2), (4,2,5), (5,6,7), (7,6,1)
    
    addEdge(graph, 0, 1, 2.0);  // (1,2,2)
    addEdge(graph, 0, 3, 1.0);  // (1,4,1)
    addEdge(graph, 1, 4, 10.0); // (2,5,10)
    addEdge(graph, 1, 3, 3.0);  // (2,4,3)
    addEdge(graph, 2, 5, 5.0);  // (3,6,5)
    addEdge(graph, 3, 2, 2.0);  // (4,3,2)
    addEdge(graph, 3, 1, 5.0);  // (4,2,5)
    addEdge(graph, 4, 5, 7.0);  // (5,6,7)
    addEdge(graph, 6, 5, 1.0);  // (7,6,1)
    
    return graph;
}

// Print graph specifically for Figure 9.20
void printFigure920Graph(Graph* graph) {
    printf("\nFigure 9.20 Graph (vertices shown as 1-7):\n");
    printf("==========================================\n");
    
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* current = graph->array[v].head;
        
        printf("Vertex %d: ", v + 1);
        
        if (current == NULL) {
            printf("No outgoing edges");
        } else {
            while (current != NULL) {
                printf("-> %d(%.2f) ", current->dest + 1, current->weight);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}
