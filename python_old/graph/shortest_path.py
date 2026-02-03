"""
Shortest Path Algorithms: Dijkstra and Bellman-Ford
Demonstrates single-source shortest path algorithms
"""

import heapq
from typing import Dict, List, Tuple, Optional, Set
from graph_class import Graph


class ShortestPath:
    """Class containing shortest path algorithm implementations."""
    
    def __init__(self, graph: Graph):
        self.graph = graph
    
    def dijkstra(self, start: str) -> Tuple[Dict[str, float], Dict[str, Optional[str]]]:
        """
        Dijkstra's algorithm for shortest paths from a single source.
        Works only with non-negative edge weights.
        
        Args:
            start: Source vertex
            
        Returns:
            Tuple of (distances, previous_vertices)
        """
        if start not in self.graph.vertices:
            raise ValueError(f"Vertex {start} not in graph")
        
        # Initialize distances and previous vertices
        distances = {vertex: float('infinity') for vertex in self.graph.vertices}
        previous = {vertex: None for vertex in self.graph.vertices}
        distances[start] = 0
        
        # Priority queue: (distance, vertex)
        pq = [(0, start)]
        visited = set()
        
        print(f"Dijkstra's algorithm starting from {start}")
        print("Step-by-step execution:")
        
        step = 1
        while pq:
            current_distance, current_vertex = heapq.heappop(pq)
            
            if current_vertex in visited:
                continue
            
            visited.add(current_vertex)
            print(f"  Step {step}: Processing vertex {current_vertex} (distance: {current_distance})")
            
            # Relax all edges from current vertex
            for neighbor, weight in self.graph.get_neighbors(current_vertex):
                if neighbor in visited:
                    continue
                
                new_distance = current_distance + weight
                
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    previous[neighbor] = current_vertex
                    heapq.heappush(pq, (new_distance, neighbor))
                    print(f"    Updated distance to {neighbor}: {new_distance}")
            
            step += 1
        
        return distances, previous
    
    def bellman_ford(self, start: str) -> Tuple[Dict[str, float], Dict[str, Optional[str]], bool]:
        """
        Bellman-Ford algorithm for shortest paths from a single source.
        Can handle negative edge weights and detects negative cycles.
        
        Args:
            start: Source vertex
            
        Returns:
            Tuple of (distances, previous_vertices, has_negative_cycle)
        """
        if start not in self.graph.vertices:
            raise ValueError(f"Vertex {start} not in graph")
        
        # Initialize distances and previous vertices
        distances = {vertex: float('infinity') for vertex in self.graph.vertices}
        previous = {vertex: None for vertex in self.graph.vertices}
        distances[start] = 0
        
        print(f"Bellman-Ford algorithm starting from {start}")
        print("Relaxing edges |V|-1 = {} times".format(len(self.graph.vertices) - 1))
        
        # Relax edges |V| - 1 times
        for i in range(len(self.graph.vertices) - 1):
            print(f"\nIteration {i + 1}:")
            any_update = False
            
            for u, v, weight in self.graph.edges:
                if distances[u] != float('infinity') and distances[u] + weight < distances[v]:
                    old_distance = distances[v]
                    distances[v] = distances[u] + weight
                    previous[v] = u
                    any_update = True
                    print(f"  Relaxed edge ({u}, {v}): {old_distance} -> {distances[v]}")
            
            if not any_update:
                print("  No updates in this iteration - algorithm can terminate early")
                break
        
        # Check for negative cycles
        print("\nChecking for negative cycles:")
        has_negative_cycle = False
        for u, v, weight in self.graph.edges:
            if distances[u] != float('infinity') and distances[u] + weight < distances[v]:
                print(f"  Negative cycle detected: edge ({u}, {v}) can still be relaxed")
                has_negative_cycle = True
                break
        
        if not has_negative_cycle:
            print("  No negative cycles detected")
        
        return distances, previous, has_negative_cycle
    
    def reconstruct_path(self, start: str, end: str, previous: Dict[str, Optional[str]]) -> Optional[List[str]]:
        """
        Reconstruct shortest path from start to end using previous vertices.
        
        Args:
            start: Source vertex
            end: Destination vertex
            previous: Dictionary of previous vertices from shortest path algorithm
            
        Returns:
            List of vertices forming the shortest path, or None if no path exists
        """
        if end not in previous or previous[end] is None and end != start:
            return None
        
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = previous[current]
        
        return path[::-1]  # Reverse to get start -> end
    
    def floyd_warshall(self) -> Tuple[Dict[str, Dict[str, float]], Dict[str, Dict[str, Optional[str]]]]:
        """
        Floyd-Warshall algorithm for all-pairs shortest paths.
        
        Returns:
            Tuple of (distance_matrix, next_vertex_matrix)
        """
        vertices = list(self.graph.vertices)
        n = len(vertices)
        
        # Initialize distance matrix
        dist = {}
        next_vertex = {}
        
        for u in vertices:
            dist[u] = {}
            next_vertex[u] = {}
            for v in vertices:
                if u == v:
                    dist[u][v] = 0
                    next_vertex[u][v] = v
                else:
                    dist[u][v] = float('infinity')
                    next_vertex[u][v] = None
        
        # Initialize with edge weights
        for u, v, weight in self.graph.edges:
            dist[u][v] = weight
            next_vertex[u][v] = v
        
        print("Floyd-Warshall algorithm - all-pairs shortest paths")
        print("Initial distance matrix:")
        self._print_distance_matrix(dist, vertices)
        
        # Floyd-Warshall main loop
        for k in range(n):
            print(f"\nIteration k={k} (intermediate vertex: {vertices[k]}):")
            for i in range(n):
                for j in range(n):
                    u, v, w = vertices[i], vertices[j], vertices[k]
                    
                    if dist[u][w] + dist[w][v] < dist[u][v]:
                        old_dist = dist[u][v]
                        dist[u][v] = dist[u][w] + dist[w][v]
                        next_vertex[u][v] = next_vertex[u][w]
                        print(f"  Updated dist[{u}][{v}]: {old_dist} -> {dist[u][v]}")
        
        return dist, next_vertex
    
    def _print_distance_matrix(self, dist: Dict[str, Dict[str, float]], vertices: List[str]) -> None:
        """Helper method to print distance matrix."""
        print("   ", end="")
        for v in vertices:
            print(f"{v:>8}", end="")
        print()
        
        for u in vertices:
            print(f"{u}: ", end="")
            for v in vertices:
                if dist[u][v] == float('infinity'):
                    print("     inf", end="")
                else:
                    print(f"{dist[u][v]:>8.1f}", end="")
            print()
    
    def find_shortest_path(self, start: str, end: str, algorithm: str = 'dijkstra') -> Optional[List[str]]:
        """
        Find shortest path between two vertices using specified algorithm.
        
        Args:
            start: Source vertex
            end: Destination vertex
            algorithm: 'dijkstra' or 'bellman_ford'
            
        Returns:
            List of vertices forming shortest path, or None if no path exists
        """
        if algorithm == 'dijkstra':
            distances, previous = self.dijkstra(start)
        elif algorithm == 'bellman_ford':
            distances, previous, has_cycle = self.bellman_ford(start)
            if has_cycle:
                print("Warning: Negative cycle detected, shortest paths may not be well-defined")
        else:
            raise ValueError("Algorithm must be 'dijkstra' or 'bellman_ford'")
        
        return self.reconstruct_path(start, end, previous)


def demonstrate_shortest_path_algorithms():
    """Demonstrate shortest path algorithms with examples."""
    
    print("=" * 70)
    print("SHORTEST PATH ALGORITHMS DEMONSTRATION")
    print("=" * 70)
    
    # Create sample graphs
    print("\n1. Creating Sample Graphs")
    print("-" * 30)
    
    # Graph for Dijkstra (non-negative weights)
    dijkstra_graph = Graph(directed=True)
    dijkstra_graph.add_edge('A', 'B', 4)
    dijkstra_graph.add_edge('A', 'C', 2)
    dijkstra_graph.add_edge('B', 'C', 1)
    dijkstra_graph.add_edge('B', 'D', 5)
    dijkstra_graph.add_edge('C', 'D', 8)
    dijkstra_graph.add_edge('C', 'E', 10)
    dijkstra_graph.add_edge('D', 'E', 2)
    
    print("Dijkstra Graph (non-negative weights):")
    dijkstra_graph.print_adjacency_list()
    
    # Graph for Bellman-Ford (with negative weights)
    bellman_graph = Graph(directed=True)
    bellman_graph.add_edge('A', 'B', 4)
    bellman_graph.add_edge('A', 'C', 2)
    bellman_graph.add_edge('B', 'C', -3)  # Negative weight
    bellman_graph.add_edge('B', 'D', 5)
    bellman_graph.add_edge('C', 'D', 1)
    bellman_graph.add_edge('D', 'E', 2)
    bellman_graph.add_edge('E', 'B', -1)  # Negative weight
    
    print("\nBellman-Ford Graph (with negative weights):")
    bellman_graph.print_adjacency_list()
    
    # Demonstrate Dijkstra's algorithm
    print("\n2. Dijkstra's Algorithm")
    print("-" * 30)
    dijkstra_sp = ShortestPath(dijkstra_graph)
    distances, previous = dijkstra_sp.dijkstra('A')
    
    print(f"\nFinal distances from A: {distances}")
    print(f"Previous vertices: {previous}")
    
    # Find specific paths
    print("\nShortest paths from A:")
    for vertex in dijkstra_graph.vertices:
        if vertex != 'A':
            path = dijkstra_sp.reconstruct_path('A', vertex, previous)
            if path:
                path_str = " -> ".join(path)
                print(f"  A to {vertex}: {path_str} (distance: {distances[vertex]})")
            else:
                print(f"  A to {vertex}: No path")
    
    # Demonstrate Bellman-Ford algorithm
    print("\n3. Bellman-Ford Algorithm")
    print("-" * 35)
    bellman_sp = ShortestPath(bellman_graph)
    distances, previous, has_cycle = bellman_sp.bellman_ford('A')
    
    print(f"\nFinal distances from A: {distances}")
    print(f"Previous vertices: {previous}")
    print(f"Has negative cycle: {has_cycle}")
    
    # Demonstrate Floyd-Warshall
    print("\n4. Floyd-Warshall Algorithm")
    print("-" * 35)
    floyd_dist, floyd_next = dijkstra_sp.floyd_warshall()
    
    print("\nFinal all-pairs distance matrix:")
    dijkstra_sp._print_distance_matrix(floyd_dist, list(dijkstra_graph.vertices))
    
    # Compare algorithms
    print("\n5. Algorithm Comparison")
    print("-" * 25)
    print("Dijkstra vs Bellman-Ford:")
    print("  Dijkstra: O((V + E) log V) - faster for non-negative weights")
    print("  Bellman-Ford: O(VE) - handles negative weights, detects cycles")
    print("  Floyd-Warshall: O(V³) - all-pairs shortest paths")
    
    # Visual representation
    print("\n6. Visual Graph Representation")
    print("-" * 35)
    print("Dijkstra Graph:")
    print("    A --4--> B --5--> D")
    print("    |        |        |")
    print("    2        1        2")
    print("    |        |        |")
    print("    C --10--> E <-----+")
    print("    |")
    print("    8")
    print("    |")
    print("    D")


if __name__ == "__main__":
    demonstrate_shortest_path_algorithms()
