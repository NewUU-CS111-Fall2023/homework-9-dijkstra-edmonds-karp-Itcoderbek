#O(V + E log V), where V is the number of nodes, and E is the number of edges. 
import heapq

def dijkstra(graph, start):
    # Initialize distances dictionary with infinity for all nodes except the start node
    # O(V), where V is the number of nodes in the graph.
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    
    # Priority queue to keep track of nodes with their distances
    priority_queue = [(0, start)]
    
    while priority_queue:
        #O(E), where E is the number of edges.
        current_distance, current_node = heapq.heappop(priority_queue)
        
        # Check if the current distance is smaller than the stored distance
        if current_distance > distances[current_node]:
            continue
        
        # Iterate through neighbors of the current node
        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight
            
            # Update distance if a shorter path is found
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))
    
    return distances

# Example graph represented as an adjacency list
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}

start_node = 'A'
shortest_distances = dijkstra(graph, start_node)

print(f"Shortest distances from node {start_node}: {shortest_distances}")
