#include <iostream>   // For input and output (cout, endl, etc.)
#include <queue>      // For using the queue data structure

using namespace std;

// -------------------------------------------------------------
// Function: BFS (Breadth-First Search)
// This function performs a BFS traversal starting from a given vertex (vtx)
// A is the adjacency matrix of the graph
// n is the number of vertices in the graph
// -------------------------------------------------------------
void BFS(int vtx, int A[][8], int n) {
    queue<int> Q;        // Queue to keep track of vertices to visit
    int visited[8] {0};  // Array to mark visited vertices (0 = not visited, 1 = visited)

    // ---------- Step 1: Start from the given vertex ----------
    cout << vtx << ", " << flush;  // Print the starting vertex
                                   // 'flush' forces the output to appear immediately on the screen
    visited[vtx] = 1;              // Mark the starting vertex as visited
    Q.emplace(vtx);                // Add (enqueue) the starting vertex into the queue

    // ---------- Step 2: Explore the graph ----------
    // Continue until there are no more vertices in the queue
    while (!Q.empty()) {
        int u = Q.front();  // Get the vertex at the front of the queue (current vertex)
        Q.pop();            // Remove it from the queue

        // Check all vertices to find the ones connected to 'u'
        for (int v = 1; v <= n; v++) {
            // If there is an edge between u and v, and v is not yet visited
            if (A[u][v] == 1 && visited[v] == 0) {
                cout << v << ", " << flush;  // Print the vertex as visited
                visited[v] = 1;              // Mark it as visited
                Q.emplace(v);                // Enqueue it for further exploration
            }
        }
    }

    cout << endl;  // Move to a new line after finishing BFS
}

// -------------------------------------------------------------
// Main Function
// Creates a graph using an adjacency matrix and runs BFS
// -------------------------------------------------------------
int main() {
    // Adjacency matrix representation of the graph
    // 0 means no edge, 1 means there is an edge between two vertices
    int A[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},  // 0th row (not used)
        {0, 0, 1, 1, 1, 0, 0, 0},  // Connections for vertex 1
        {0, 1, 0, 1, 0, 0, 0, 0},  // Connections for vertex 2
        {0, 1, 1, 0, 1, 1, 0, 0},  // Connections for vertex 3
        {0, 1, 0, 1, 0, 1, 0, 0},  // Connections for vertex 4
        {0, 0, 0, 1, 1, 0, 1, 1},  // Connections for vertex 5
        {0, 0, 0, 0, 0, 1, 0, 0},  // Connections for vertex 6
        {0, 0, 0, 0, 0, 1, 0, 0}   // Connections for vertex 7
    };

    // Run BFS starting from vertex 1
    cout << "Vertex: 1 -> " << flush;
    BFS(1, A, 8);

    // Run BFS starting from vertex 4
    cout << "Vertex: 4 -> " << flush;
    BFS(4, A, 8);

    return 0;
}
