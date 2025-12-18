#include "graph.h"

void testFigure91() {
    printf("=== PART 1: Figure 9.1 Graph (Topological Sort) ===\n");
    
    // Adjacency matrix from Figure 9.1 (7 vertices)
    int graphMatrix[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0}
    };
    
    int vertices = 7;
    
    printf("(a) Building graph from adjacency matrix...\n");
    Graph* graph = buildGraphFromMatrix(graphMatrix, vertices);
    printGraph(graph);
    
    // Topological sort using adjacency matrix
    topologicalSortMatrix(graphMatrix, vertices);
    
    // Topological sort using adjacency list
    topologicalSortList(graph);
    
    // Free allocated memory
    for (int i = 0; i < vertices; i++) {
        AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->array);
    free(graph);
    
    printf("\n=== Figure 9.1 Test Completed ===\n\n");
}

void testFigure920() {
    printf("\n=== PART 2: Figure 9.20 Graph (Dijkstra Algorithm) ===\n");
    printf("Vertices: 1 to 7 (displayed as 1-7)\n");
    printf("Edges with weights:\n");
    printf("  (1,2,2), (1,4,1), (2,5,10), (2,4,3), (3,6,5),\n");
    printf("  (4,3,2), (4,2,5), (5,6,7), (7,6,1)\n");
    
    // Create Figure 9.20 graph
    Graph* graph = createFigure920Graph();
    
    printFigure920Graph(graph);
    
    // Run Dijkstra from vertex 0 (which is vertex 1 in problem)
    printf("Running Dijkstra algorithm from source vertex 1:\n");
    dijkstra(graph, 0);
    
    // Free allocated memory
    for (int i = 0; i < 7; i++) {
        AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->array);
    free(graph);
    
    printf("\n=== Figure 9.20 Test Completed ===\n");
}

int main() {
    printf("================================================================\n");
    printf("        GRAPH ALGORITHMS IMPLEMENTATION PROJECT\n");
    printf("================================================================\n\n");
    
    // Test Figure 9.1 (Topological Sort)
    testFigure91();
    
    printf("\n");
    printf("================================================================\n");
    printf("\n");
    
    // Test Figure 9.20 (Dijkstra Algorithm)
    testFigure920();
    
    printf("\n================================================================\n");
    printf("        PROGRAM COMPLETED SUCCESSFULLY\n");
    printf("================================================================\n");
    
    return 0;
}
