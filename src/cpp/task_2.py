#   the overall time complexity of 
# the edmonds_karp algorithm is O(VE^2) in the worst case,
# where V is the number of vertices and E is the number of edges
from collections import deque

class Edge:
    def __init__(self, t, cap, flow):
        self.t = t      # Target vertex
        self.cap = cap  # Capacity of the edge
        self.flow = flow # Flow through the edge

def edmonds_karp(graph, s, t):
    def bfs():
        #O(V + E), where V is the number of vertices and E is the number of edges.
        q = deque()
        q.append(s)
        pred = [-1] * len(graph)

        while q and pred[t] == -1:
            cur = q.popleft()

            for e in graph[cur]:
                if pred[e.t] == -1 and e.t != s and e.cap > e.flow:
                    pred[e.t] = e
                    q.append(e.t)

        return pred

    def augment(pred):
        # O(V).
        path_flow = float('inf')
        current = t

        while current != s:
            edge = pred[current]
            path_flow = min(path_flow, edge.cap - edge.flow)
            current = edge.t

        current = t
        while current != s:
            edge = pred[current]
            edge.flow += path_flow
            graph[edge.t].append(Edge(current, 0, -path_flow))
            current = edge.t

        return path_flow

    max_flow = 0
    pred = bfs()

    while pred[t] != -1:
        path_flow = augment(pred)
        max_flow += path_flow
        pred = bfs()
        # O(VE)

    return max_flow

# Example Usage:
# Construct a graph as an adjacency list
graph = [[] for _ in range(4)]  # Assuming 4 vertices in the graph

# Add directed edges with capacities
graph[0].append(Edge(1, 10, 0))
graph[0].append(Edge(2, 5, 0))
graph[1].append(Edge(2, 15, 0))
graph[1].append(Edge(3, 10, 0))
graph[2].append(Edge(3, 10, 0))

source = 0
sink = 3

max_flow = edmonds_karp(graph, source, sink)
print(f"Maximum Flow: {max_flow}")
