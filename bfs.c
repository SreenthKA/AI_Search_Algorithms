#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 26

// Structure to represent a node in the graph
struct Node {
    char label;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
};

// Function to initialize a graph
void initializeGraph(struct Graph* graph, int numNodes) {
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        graph->adjacencyList[i] = NULL;
    }
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, char src, char dest) {
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->label = dest;
    newNode->next = graph->adjacencyList[srcIndex];
    graph->adjacencyList[srcIndex] = newNode;
}

// Function to perform Breadth-First Search
bool BFS(struct Graph* graph, char startNode, char targetNode) {
    int visited[MAX_NODES] = {0}; // Initialize all nodes as unvisited
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    int parent[MAX_NODES]; // Store the parent of each node for reconstructing the path
    for (int i = 0; i < MAX_NODES; i++) {
        parent[i] = -1; // Initialize parent array
    }

    int startNodeIndex = startNode - 'A';
    int targetNodeIndex = targetNode - 'A';

    visited[startNodeIndex] = 1;
    queue[rear++] = startNodeIndex;

    while (front < rear) {
        int currentNodeIndex = queue[front++];
        char currentNode = currentNodeIndex + 'A';

        if (currentNode == targetNode) {
            // Found the target node, reconstruct and print the path
            printf("Path: %c", targetNode);
            char current = targetNode;
            while (parent[current - 'A'] != -1) {
                current = parent[current - 'A'] + 'A';
                printf(" <- %c ", current);
            }
            printf("\n");
            return true; // Path found
        }

        struct Node* currentNeighbor = graph->adjacencyList[currentNodeIndex];
        while (currentNeighbor != NULL) {
            char neighborNode = currentNeighbor->label;
            int neighborNodeIndex = neighborNode - 'A';
            if (!visited[neighborNodeIndex]) {
                visited[neighborNodeIndex] = 1;
                parent[neighborNodeIndex] = currentNodeIndex;
                queue[rear++] = neighborNodeIndex;
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    return false; // No path found
}

int main() {
    struct Graph graph;
    int numNodes, numEdges;

    printf("Enter the number of nodes (maximum %d): ", MAX_NODES);
    scanf("%d", &numNodes);

    if (numNodes > MAX_NODES) {
        printf("Number of nodes exceeds the maximum limit.\n");
        return 1;
    }

    initializeGraph(&graph, numNodes);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        char src, dest;
        printf("Enter source and destination of edge %d (letters A to Z): ", i + 1);
        scanf(" %c %c", &src, &dest);
        addEdge(&graph, src, dest);
    }

    char startNode, targetNode;
    printf("Enter the source node (letter A to Z): ");
    scanf(" %c", &startNode);
    printf("Enter the target node (letter A to Z): ");
    scanf(" %c", &targetNode);

    printf("Finding path from Node %c to Node %c using BFS:\n", startNode, targetNode);
    if (!BFS(&graph, startNode, targetNode)) {
        printf("No path found.\n");
    }

    return 0;
}
