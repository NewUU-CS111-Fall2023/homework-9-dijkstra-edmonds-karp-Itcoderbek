#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int INF = INT_MAX;
    
    // Create an adjacency list to represent the graph
    //time complexity of O(E), where E is the number of edges.
    vector<vector<pair<int, int>>> graph(n + 1); // 1-indexed graph
    
    for (const auto& time : times) {
        int u = time[0];
        int v = time[1];
        int w = time[2];
        graph[u].emplace_back(v, w);
    }
    
    // Initialize distances array with INF, and distance from source to itself as 0
    vector<int> distance(n + 1, INF);
    distance[k] = 0;
    
    // Min heap to get the node with the minimum distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});
    
    while (!pq.empty()) {
        //the time complexity of the while loop is O((N + E) * log N).
        int curNode = pq.top().second;
        int curDist = pq.top().first;
        pq.pop();
        
        if (curDist > distance[curNode]) {
            continue; // Skip if we have found a shorter path to this node
        }
        
        // Update distances for all neighbors of the current node
        for (const auto& neighbor : graph[curNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            int newDist = curDist + weight;
            
            if (newDist < distance[nextNode]) {
                distance[nextNode] = newDist;
                pq.push({newDist, nextNode});
            }
        }
    }
    
    // Check if all nodes are reachable and find the maximum distance
    //O(N).
    int maxDistance = *max_element(distance.begin() + 1, distance.end());
    
    return (maxDistance == INF) ? -1 : maxDistance;
}

int main() {
    // Example usage
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4; // Number of nodes
    int k = 2; // Source node

    int result = networkDelayTime(times, n, k);

    cout << "Minimum time it takes for all nodes to receive the signal: ";
    if (result == -1) {
        cout << "Not possible" << endl;
    } else {
        cout << result << " units" << endl;
    }

    return 0;
}
