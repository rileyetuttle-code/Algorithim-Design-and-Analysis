#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// -----------------------------------------------------------------------------
// Function: bfs_shortest_path
// Purpose:  Find the shortest path between two people (nodes) in a graph
// Method:   Breadth-First Search (BFS)
// -----------------------------------------------------------------------------
vector<int> bfs_shortest_path(unordered_map<int, vector<int>>& graph, int start, int goal) {
    unordered_set<int> visited;    // Keeps track of visited nodes
    queue<vector<int>> q;          // Queue holds paths (each element is a path vector)
    q.push({ start });             // Start BFS from the 'start' node

    // If start and goal are the same, return the single node
    if (start == goal)
        return { start };

    // -------------------------------------------------------------------------
    // Begin BFS traversal
    // -------------------------------------------------------------------------
    while (!q.empty()) {
        // Get the first path from the queue
        vector<int> path = q.front();
        q.pop();

        // Get the last node in this path (current node)
        int node = path.back();

        // If this node has not been visited yet
        if (visited.find(node) == visited.end()) {
            visited.insert(node);  // Mark it as visited

            // Explore all neighbors (friends) of this node
            for (int neighbor : graph[node]) {
                // Create a new path that extends the current one
                vector<int> new_path = path;
                new_path.push_back(neighbor);

                // Add the new path to the queue for future exploration
                q.push(new_path);

                // If we reached the goal, return this path
                if (neighbor == goal)
                    return new_path;
            }
        }
    }

    // If we exit the loop, it means no connection exists between start and goal
    return {};
}

// -----------------------------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------------------------
int main() {
    // -------------------------------------------------------------------------
    // Step 1: Define the Facebook friendship graph as an adjacency list
    // Each key represents a person (node), and the vector contains their friends
    // -------------------------------------------------------------------------
    unordered_map<int, vector<int>> facebook_graph = {
        {0, {1, 2}},
        {1, {0, 3, 4}},
        {2, {0, 5}},
        {3, {1}},
        {4, {1, 6}},
        {5, {2}},
        {6, {4}},
        {7, {8}},
        {8, {7, 9}},
        {9, {8}}
    };

    // -------------------------------------------------------------------------
    // Step 2: Find the shortest path between two people (for example, 0 and 6)
    // -------------------------------------------------------------------------
    vector<int> shortest_path = bfs_shortest_path(facebook_graph, 0, 6);

    // -------------------------------------------------------------------------
    // Step 3: Display the result
    // -------------------------------------------------------------------------
    if (!shortest_path.empty()) {
        cout << "Shortest path from 0 to 6: ";
        for (int person : shortest_path)
            cout << person << " ";
        cout << endl;
    } else {
        cout << "No connection found between 0 and 6." << endl;
    }

    return 0;
}
