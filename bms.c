#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct Node {
    char label;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int V; // Number of vertices
    struct Node** adjList; // Array of adjacency lists
};

// Function to create a new node
struct Node* createNode(char label) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->label = label;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'V' vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, char src, char dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src - 'A'];
    graph->adjList[src - 'A'] = newNode;

    // For an undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest - 'A'];
    graph->adjList[dest - 'A'] = newNode;
}

// Utility function to print a path
void printPath(char path[], int pathLength) {
    for (int i = 0; i < pathLength; i++) {
        printf("%c", path[i]);
        if (i < pathLength - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Recursive function to find and print all paths from src to dest
void findAllPaths(struct Graph* graph, char src, char dest, bool visited[], char path[], int pathLength) {
    visited[src - 'A'] = true;
    path[pathLength] = src;
    pathLength++;

    if (src == dest) {
        // We have reached the destination, print the path
        printPath(path, pathLength);
    } else {
        // Recur for all adjacent vertices of the current vertex
        struct Node* current = graph->adjList[src - 'A'];
        while (current != NULL) {
            char adjacentNode = current->label;
            if (!visited[adjacentNode - 'A']) {
                findAllPaths(graph, adjacentNode, dest, visited, path, pathLength);
            }
            current = current->next;
        }
    }

    // Mark the current node as unvisited to explore other paths
    visited[src - 'A'] = false;
}

// Function to find and print all paths from src to dest
void findAndPrintAllPaths(struct Graph* graph, char src, char dest) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    char* path = (char*)malloc(graph->V * sizeof(char));
    int pathLength = 0;

    printf("Paths from %c to %c:\n", src, dest);
    findAllPaths(graph, src, dest, visited, path, pathLength);

    free(visited);
    free(path);
}

// Function to print the graph
void printGraph(struct Graph* graph) {
    printf("Graph Representation:\n");
    for (int i = 0; i < graph->V; i++) {
        struct Node* current = graph->adjList[i];
        printf("Node %c: ", 'A' + i);
        while (current != NULL) {
            printf("%c -> ", current->label);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of nodes (A to Z): ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter the edges (source node and destination node as letters A to Z):\n");
    for (int i = 0; i < E; i++) {
        char src, dest;
        scanf(" %c %c", &src, &dest);
        addEdge(graph, src, dest);
    }

    printGraph(graph);

    char src, dest;
    printf("Enter source node (A to Z): ");
    scanf(" %c", &src);
    printf("Enter destination node (A to Z): ");
    scanf(" %c", &dest);

    findAndPrintAllPaths(graph, src, dest);

    return 0;
}
