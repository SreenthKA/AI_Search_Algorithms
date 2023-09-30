#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NODES 26

struct Graph 
{
    int numNodes;
    char adjMatrix[MAX_NODES][MAX_NODES];
};

struct Graph* createGraph(int numNodes) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;

    for (int i = 0; i < numNodes; ++i) 
    {
        for (int j = 0; j < numNodes; ++j) 
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(struct Graph* graph, char src, char dest) 
{
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    graph->adjMatrix[srcIndex][destIndex] = 1;
}

bool DFS(struct Graph* graph, char src, char dest, int visited[], char path[], int pathIndex) 
{
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';

    visited[srcIndex] = 1;
    path[pathIndex] = src;
    pathIndex++;

    if (src == dest) 
    {
        printf("Path from %c to %c: ", path[0], path[pathIndex - 1]);
        for (int i = 0; i < pathIndex; ++i) 
        {
            if (i != 0) 
            {
                printf("->");
            }
            printf("%c", path[i]);
        }
        printf("\n");
        return true;
    }

    for (int i = 0; i < graph->numNodes; ++i) 
    {
        if (!visited[i] && graph->adjMatrix[srcIndex][i] == 1) 
        {
            if (DFS(graph, 'A' + i, dest, visited, path, pathIndex)) 
            {
                return true;
            }
        }
    }

    pathIndex--;
    visited[srcIndex] = 0;

    return false;
}

int main() 
{
    int numNodes, numEdges;
    printf("Enter the number of nodes (maximum %d): ", MAX_NODES);
    scanf("%d", &numNodes);

    if (numNodes > MAX_NODES) 
    {
        printf("Number of nodes exceeds the maximum limit.\n");
        return 1;
    }

    struct Graph* graph = createGraph(numNodes);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; ++i) 
    {
        char src, dest;
        printf("Enter edge %d (names of two nodes with space): ", i + 1);
        scanf(" %c %c", &src, &dest);
        addEdge(graph, src, dest);
    }

    char src, dest;
    printf("Enter the source node: ");
    scanf(" %c", &src);

    printf("Enter the destination node: ");
    scanf(" %c", &dest);

    int visited[MAX_NODES] = {0};
    char path[MAX_NODES];
    if (!DFS(graph, src, dest, visited, path, 0))
        printf("There is no path from %c to %c.\n", src, dest);

    return 0;
}
