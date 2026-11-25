#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
 
const int INF = INT_MAX;
 
void dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INF);
    distances[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    /* pair<int, int>: The priority queue stores pairs of integers. The first element of the pair represents the distance (or priority), and the second element represents the node.
 
vector<pair<int, int>>: This is the underlying container that stores the elements of the priority queue.
 
greater<pair<int, int>>: This is the comparison function. By default, a priority queue in C++ is a max-heap, but for Dijkstra's algorithm, we need a min-heap to always extract the node with the smallest distance first. Using greater<pair<int, int>> ensures that the priority queue acts as a min-heap.
*/
    pq.push({0, start});
    
    while (!pq.empty()) {
        int distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if (distance > distances[node])
            continue;
        
        for (auto neighbor : graph[node]) {
            int next_node = neighbor.first;
            int weight = neighbor.second;
            int new_dist = distance + weight;
            
            if (new_dist < distances[next_node]) {
                distances[next_node] = new_dist;
                pq.push({new_dist, next_node});
            }
        }
    }
    
    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << distances[i] << '\n';
    }
}
 
int main() {
    int n = 8; // number of nodes
    vector<vector<pair<int, int>>> graph(n);
    
    // Example graph
    graph[0] = {{1, 6}, {2, 4}};
    graph[1] = {{0, 6}, {2, 2}, {3, 5}, {4, 3}};
    graph[2] = {{0, 4}, {1, 2}, {4, 5}};
    graph[3] = {{1, 5}, {4, 2}, {5, 4}, {6, 6}};
    graph[4] = {{1, 3}, {2, 5}, {3, 2}, {5, 6}};
    graph[5] = {{3, 4}, {4, 6}, {6, 2}, {7, 3}};
    graph[6] = {{3, 6}, {5, 2}, {7, 1}};
    graph[7] = {{5, 3}, {6, 1}};
    dijkstra(graph, 0); // Start from node 0
    
    return 0;
}
 
 