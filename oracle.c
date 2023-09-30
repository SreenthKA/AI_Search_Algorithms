#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 100

// Structure to represent an edge in the graph
struct Edge {
    char from[10];
    char to[10];
    int cost;
};

// Structure to represent a node in the graph
struct Node {
    char name[10];
};

// Function to perform Uniform-Cost Search
void uniformCostSearch(struct Node nodes[], struct Edge edges[], int numNodes, int numEdges, char source[], char destination[]) {
    int visited[MAX_NODES] = {0}; // To keep track of visited nodes
    int distance[MAX_NODES];     // To store the minimum distance to each node
    int parent[MAX_NODES];       // To store the parent node for each node in the path

    // Initialize distances to infinity and parent to -1
    for (int i = 0; i < numNodes; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Find the index of the source node
    int sourceIndex = -1;
    for (int i = 0; i < numNodes; i++) {
        if (strcmp(nodes[i].name, source) == 0) {
            sourceIndex = i;
            break;
        }
    }

    // Initialize distance to the source node as 0
    distance[sourceIndex] = 0;

    // Uniform-Cost Search loop
    for (int i = 0; i < numNodes - 1; i++) {
        int minDistance = INT_MAX;
        int u = -1;

        // Find the node with the minimum distance that has not been visited yet
        for (int j = 0; j < numNodes; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                u = j;
            }
        }

        if (u == -1) {
            break; // No more reachable nodes
        }

        visited[u] = 1;

        // Relaxation step - Update distance for neighboring nodes
        for (int j = 0; j < numEdges; j++) {
            if (strcmp(edges[j].from, nodes[u].name) == 0) {
                int v = -1;
                for (int k = 0; k < numNodes; k++) {
                    if (strcmp(nodes[k].name, edges[j].to) == 0) {
                        v = k;
                        break;
                    }
                }
                if (v != -1) {
                    int edgeCost = edges[j].cost;

                    if (!visited[v] && distance[u] + edgeCost < distance[v]) {
                        distance[v] = distance[u] + edgeCost;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // Find the index of the destination node
    int destinationIndex = -1;
    for (int i = 0; i < numNodes; i++) {
        if (strcmp(nodes[i].name, destination) == 0) {
            destinationIndex = i;
            break;
        }
    }

    // Print the path from source to destination
    if (distance[destinationIndex] != INT_MAX) {
        printf("Shortest path from %s to %s:\n", source, destination);
        int current = destinationIndex;
        while (current != -1) {
            printf("%s", nodes[current].name);
            if (parent[current] != -1) {
                printf(" <- ");
            }
            current = parent[current];
        }
        printf("\nMinimum Cost: %d\n", distance[destinationIndex]);
    } else {
        printf("No path from %s to %s\n", source, destination);
    }
}

int main() {
    struct Node nodes[MAX_NODES];
    struct Edge edges[MAX_NODES];
    int numNodes, numEdges;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the names of nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%s", nodes[i].name);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (from to cost):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%s %s %d", edges[i].from, edges[i].to, &edges[i].cost);
    }

    char source[10], destination[10];
    printf("Enter the source node: ");
    scanf("%s", source);
    printf("Enter the destination node: ");
    scanf("%s", destination);

    uniformCostSearch(nodes, edges, numNodes, numEdges, source, destination);

    return 0;
}
