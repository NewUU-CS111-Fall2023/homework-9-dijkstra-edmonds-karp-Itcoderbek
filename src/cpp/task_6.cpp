#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
struct Flight {
    int from;
    int to;
    int distance;
    int ars; // Avia Refueling Station availability
};

// Helper function to find the shortest path with at most k stops
int findShortestPath(int src, int dst, int k, int f, const vector<Flight>& flights) {
    //O(k * n), where k is the maximum number of stops, and n is the number of flights (cities).
    const int n = flights.size();

    // Create a vector to store distances from src to all cities
    vector<vector<int>> dp(n + 1, vector<int>(k + 2, INT_MAX));

    // Initialize the source city
    dp[src][0] = 0;

    // Iterate over the number of stops
    for (int stops = 1; stops <= k + 1; ++stops) {
        // Iterate over each flight
        for (const Flight& flight : flights) {
            // If the current city is reachable within the allowed stops
            if (dp[flight.from][stops - 1] != INT_MAX) {
                // If there is enough fuel to reach the destination
                if (flight.distance <= f) {
                    dp[flight.to][stops] = min(dp[flight.to][stops], dp[flight.from][stops - 1] + flight.distance);
                }

                // If there is an Avia Refueling Station at the destination
                if (flight.ars == 1) {
                    dp[flight.to][stops] = min(dp[flight.to][stops], dp[flight.from][stops - 1]);
                }
            }
        }
    }

    // Check if the destination is reachable within the allowed stops
    int result = INT_MAX;
    for (int stops = 1; stops <= k + 1; ++stops) {
        result = min(result, dp[dst][stops]);
    }

    return (result == INT_MAX) ? -1 : result;
}

int main() {
    // Example usage
    vector<Flight> flights = {{0, 1, 100, 0}, {1, 2, 200, 1}, {0, 2, 500, 0}};
    int src = 0, dst = 2, k = 1, f = 200;

    int shortestPath = findShortestPath(src, dst, k, f, flights);

    if (shortestPath == -1) {
        cout << "No such route exists." << endl;
    } else {
        cout << "Shortest path from city " << src << " to city " << dst << " with at most " << k << " stops: " << shortestPath << endl;
    }

    return 0;
}
