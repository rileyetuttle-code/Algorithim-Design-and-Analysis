#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// A. BFS to find the shortest path between two people
vector<int> bfs_shortest_path(unordered_map<int, vector<int>>& graph, int start, int goal) {

    unordered_set<int> visited;
    queue<vector<int>> q;
    q.push({ start });

    if (start == goal)
        return { start };

    while (!q.empty()) {
        vector<int> path = q.front();
        q.pop();
        int node = path.back();

        if (visited.find(node) == visited.end()) {
            visited.insert(node);

            for (int neighbor : graph[node]) {
                vector<int> new_path = path;
                new_path.push_back(neighbor);
                q.push(new_path);

                if (neighbor == goal)
                    return new_path;
            }
        }
    }

    return {}; // Return empty vector if no connection found
}

// B. BFS to find all friends within 2 degrees of separation
vector<int> bfs_2_degrees(unordered_map<int, vector<int>>& graph, int start)
{
    unordered_map<int, int> friendDepth;
    unordered_set<int> visited;
    queue<int> q;
    vector<int> twoDegFriends;

    q.push(start);
    friendDepth[start] = 0;
    visited.insert(start);

    while(!q.empty())
    {
        int node = q.front();
        q.pop();

        if(friendDepth[node] < 2)
        {
            for(int neighbor: graph[node])
            {
                if(!visited.count(neighbor))
                {
                    visited.insert(neighbor);
                    friendDepth[neighbor] = friendDepth[node] + 1;
                    q.push(neighbor);
                    twoDegFriends.push_back(neighbor);
                }
            }
        }
    }

    return twoDegFriends;

}

// C. BFS to check if the network is fully connected
int bfs_connected_components(unordered_map<int, vector<int>>& graph) 
{
    

    unordered_set<int> visited;
    int count = 0;

    for(unordered_map<int, vector<int>>::iterator it = graph.begin(); it != graph.end(); ++it)
    {

        int start = it->first; // only way i found to get a starting value in graph without a starting parameter

        if(visited.find(start) != visited.end())
            continue; // check if node is already apart of cluster we have counted
        
        count++; // if it has not been visited, we are in a new cluster

        queue<int> q;
        visited.insert(start);
        q.push(start);

        while (!q.empty()) 
        {
            int node = q.front();
            q.pop();

            for (int neighbor : graph[node])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    } 

    return count; 
}

int main() {
    // Facebook Friends Network graph
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

    // A. Find the shortest path between two people
    vector<int> shortest_path = bfs_shortest_path(facebook_graph, 0, 6);
    if (!shortest_path.empty()) {
        cout << "Shortest path from 0 to 6: ";
        for (int person : shortest_path)
            cout << person << " ";
        cout << endl;
    } else {
        cout << "No connection found between 0 and 6." << endl;
    }

    // B. Find all friends within 2 degrees of separation
    vector<int> friends_2_degrees = bfs_2_degrees(facebook_graph, 0);
    cout << "Friends within 2 degrees of separation from 0: ";
    for (int person : friends_2_degrees)
        cout << person << " ";
    cout << endl;

    // C. Check if the network is fully connected
    int components = bfs_connected_components(facebook_graph);
    if (components == 1) {
        cout << "The network is fully connected." << endl;
    } else {
        cout << "The network has " << components << " disconnected components." << endl;
    }

    return 0;
}
