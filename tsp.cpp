#include <stdio.h>
#include <malloc.h>
#include <limits.h>
typedef struct {
    float weight;
    int city1;
    int city2;
} Edge;

void readData(float **matrix, int *n) {
    FILE *file = fopen("TSP.txt", "r");
    fscanf(file, "%d", n);

    *matrix = (float*)malloc((*n) * (*n) * sizeof(float));

    for(int i = 0; i < *n; i++) {
        for(int j = 0; j < *n; j++) {
            fscanf(file, "%f", &(*matrix)[i * (*n) + j]);
        }
    }

    fclose(file);
}

void sortEdges(Edge *edges, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

void greedyTSP(float *matrix, int n) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    int current = 0;
    visited[current] = 1;
    printf("Chu trinh di nguoi giao hang:\n");
    float totalWeight = 0;
    int countVisited = 1;
    while (countVisited < n) {
        Edge minEdge;
        minEdge.weight = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && matrix[current * n + j] < minEdge.weight) {
                minEdge.city1 = current;
                minEdge.city2 = j;
                minEdge.weight = matrix[current * n + j];
            }
        }
        current = minEdge.city2;
        visited[current] = 1;
        printf("%c%c, ", 'a' + minEdge.city1, 'a' + minEdge.city2);
        totalWeight += minEdge.weight;
        countVisited++;
    }
    printf("%c%c\nTong do dai duong di: %.2f\n", 'a' + current, 'a', totalWeight);
}
int main() {
    int n;
    float *matrix;

    readData(&matrix, &n);
    greedyTSP(matrix, n);

    free(matrix);

    return 0;
}
