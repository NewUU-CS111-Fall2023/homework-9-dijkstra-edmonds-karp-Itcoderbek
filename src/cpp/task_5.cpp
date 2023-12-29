#include <iostream>
#include <vector>
#include <queue>
#include <climits>
//the overall time complexity is O((n + |E|) * log(n * k))
using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> graph(n);

    for (const auto& flight : flights) {
        int from = flight[0];
        int to = flight[1];
        int price = flight[2];
        graph[from].emplace_back(to, price);
    }

    // Priority queue to store {cost, current city, remaining stops}
    /*
     O(n * k) elements, where n is the number of cities and k is the maximum number of stops.
    In the worst case, each city can be considered with all possible remaining stops.
    */
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    pq.emplace(0, src, k + 1);

    while (!pq.empty()) {
        //O(|E|), where |E| is the number of flights.
        auto [cost, current, stops] = pq.top();
        pq.pop();

        if (current == dst) {
            return cost;  // If the destination is reached, return the cost
        }

        if (stops > 0) {
           
            for (const auto& neighbor : graph[current]) {
                int nextCity = neighbor.first;
                int nextCost = neighbor.second;

                pq.emplace(cost + nextCost, nextCity, stops - 1);
            }
        }
    }

    return -1;  // If destination is not reached within k stops
}

int main() {
    // Example usage
    int n = 3;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src = 0, dst = 2, k = 1;

    int result = findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest price from " << src << " to " << dst << " with at most " << k << " stops: ";
    
    if (result != -1) {
        cout << result << endl;
    } else {
        cout << "No such route" << endl;
    }

    return 0;
}
