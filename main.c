#include "graph.h"

int main() {
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
    
    printf("=== Directed Graph Implementation ===\n");
    printf("Vertices: 0 to 6\n\n");
    
    printf("(a) Building graph from adjacency matrix...\n");
    Graph* graph = buildGraphFromMatrix(graphMatrix, vertices);
    printGraph(graph);
        
    topologicalSortMatrix(graphMatrix, vertices);
    
    topologicalSortList(graph);
    
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
    
    printf("\n=== Program Completed Successfully ===\n");
    
    return 0;
}