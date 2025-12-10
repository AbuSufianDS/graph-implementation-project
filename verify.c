#include <stdio.h>

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
    
    printf("Edge List:\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (graphMatrix[i][j] == 1) {
                printf("%d -> %d\n", i, j);
            }
        }
    }
    
    printf("\nIn-degree calculation:\n");
    for (int j = 0; j < 7; j++) {
        int indegree = 0;
        for (int i = 0; i < 7; i++) {
            indegree += graphMatrix[i][j];
        }
        printf("Vertex %d in-degree: %d\n", j, indegree);
    }
    
    return 0;
}
