"""
Comprehensive Graph Class Implementation
Demonstrates various graph representations and basic operations
"""

from collections import defaultdict, deque
import heapq
from typing import List, Tuple, Dict, Set, Optional, Union


class Graph:
    """
    A comprehensive graph class supporting both directed and undirected graphs
    with weighted and unweighted edges.
    """
    
    def __init__(self, directed: bool = False):
        """
        Initialize an empty graph.
        
        Args:
            directed: If True, creates a directed graph; otherwise undirected
        """
        self.vertices: Set[str] = set()
        self.adjacency_list: Dict[str, List[Tuple[str, float]]] = defaultdict(list)
        self.edges: List[Tuple[str, str, float]] = []
        self.directed = directed
        self.vertex_count = 0
        self.edge_count = 0
    
    def add_vertex(self, vertex: str) -> None:
        """Add a vertex to the graph."""
        if vertex not in self.vertices:
            self.vertices.add(vertex)
            self.vertex_count += 1
    
    def add_edge(self, u: str, v: str, weight: float = 1.0) -> None:
        """
        Add an edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            weight: Edge weight (default 1.0 for unweighted)
        """
        self.add_vertex(u)
        self.add_vertex(v)
        
        # Add edge to adjacency list
        self.adjacency_list[u].append((v, weight))
        self.edges.append((u, v, weight))
        self.edge_count += 1
        
        # For undirected graphs, add reverse edge
        if not self.directed:
            self.adjacency_list[v].append((u, weight))
    
    def get_neighbors(self, vertex: str) -> List[Tuple[str, float]]:
        """Get all neighbors of a vertex with their edge weights."""
        return self.adjacency_list.get(vertex, [])
    
    def get_all_vertices(self) -> List[str]:
        """Get list of all vertices."""
        return list(self.vertices)
    
    def get_all_edges(self) -> List[Tuple[str, str, float]]:
        """Get list of all edges."""
        return self.edges.copy()
    
    def get_vertex_degree(self, vertex: str) -> int:
        """Get the degree of a vertex."""
        return len(self.adjacency_list[vertex])
    
    def get_in_degree(self, vertex: str) -> int:
        """Get the in-degree of a vertex (for directed graphs)."""
        if not self.directed:
            return self.get_vertex_degree(vertex)
        
        in_degree = 0
        for _, neighbors in self.adjacency_list.items():
            for neighbor, _ in neighbors:
                if neighbor == vertex:
                    in_degree += 1
        return in_degree
    
    def has_edge(self, u: str, v: str) -> bool:
        """Check if an edge exists between vertices u and v."""
        for neighbor, _ in self.adjacency_list[u]:
            if neighbor == v:
                return True
        return False
    
    def get_edge_weight(self, u: str, v: str) -> Optional[float]:
        """Get the weight of edge (u, v) if it exists."""
        for neighbor, weight in self.adjacency_list[u]:
            if neighbor == v:
                return weight
        return None
    
    def remove_vertex(self, vertex: str) -> None:
        """Remove a vertex and all its incident edges."""
        if vertex not in self.vertices:
            return
        
        # Remove all edges incident to this vertex
        edges_to_remove = []
        for i, (u, v, w) in enumerate(self.edges):
            if u == vertex or v == vertex:
                edges_to_remove.append(i)
        
        # Remove edges in reverse order to maintain indices
        for i in reversed(edges_to_remove):
            del self.edges[i]
            self.edge_count -= 1
        
        # Remove from adjacency lists
        if vertex in self.adjacency_list:
            del self.adjacency_list[vertex]
        
        # Remove from other adjacency lists
        for v in self.adjacency_list:
            self.adjacency_list[v] = [(n, w) for n, w in self.adjacency_list[v] if n != vertex]
        
        self.vertices.remove(vertex)
        self.vertex_count -= 1
    
    def remove_edge(self, u: str, v: str) -> None:
        """Remove edge between vertices u and v."""
        # Remove from adjacency list
        if u in self.adjacency_list:
            self.adjacency_list[u] = [(n, w) for n, w in self.adjacency_list[u] if n != v]
        
        # For undirected graphs, remove reverse edge
        if not self.directed and v in self.adjacency_list:
            self.adjacency_list[v] = [(n, w) for n, w in self.adjacency_list[v] if n != u]
        
        # Remove from edges list
        self.edges = [(a, b, w) for a, b, w in self.edges if not (a == u and b == v)]
        self.edge_count -= 1
    
    def is_connected(self) -> bool:
        """Check if the graph is connected (for undirected graphs)."""
        if self.directed or len(self.vertices) == 0:
            return False
        
        if len(self.vertices) == 1:
            return True
        
        # Use DFS to check connectivity
        visited = set()
        start_vertex = next(iter(self.vertices))
        self._dfs_visit(start_vertex, visited)
        
        return len(visited) == len(self.vertices)
    
    def is_connected_bfs(self) -> bool:
        """
        Check if the graph is connected using BFS (for undirected graphs).
        
        Alternative implementation using BFS instead of DFS for connectivity checking.
        
        Returns:
            True if graph is connected, False otherwise
        """
        if self.directed or len(self.vertices) == 0:
            return False
        
        if len(self.vertices) == 1:
            return True
        
        # Use BFS to check connectivity
        visited = set()
        start_vertex = next(iter(self.vertices))
        self._bfs_visit(start_vertex, visited)
        
        return len(visited) == len(self.vertices)
    
    def bfs_traversal(self, start_vertex: str) -> List[str]:
        """
        Perform BFS traversal starting from given vertex.
        
        Args:
            start_vertex: Vertex to start BFS from
            
        Returns:
            List of vertices in BFS order
            
        Educational Purpose:
        - Shows level-by-level traversal order
        - Demonstrates queue-based exploration
        - Useful for understanding BFS algorithm
        """
        if start_vertex not in self.vertices:
            raise ValueError(f"Vertex {start_vertex} not in graph")
        
        visited = set()
        traversal_order = []
        queue = deque([start_vertex])
        visited.add(start_vertex)
        
        while queue:
            current_vertex = queue.popleft()
            traversal_order.append(current_vertex)
            
            for neighbor, _ in self.adjacency_list[current_vertex]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        
        return traversal_order
    
    def dfs_traversal(self, start_vertex: str) -> List[str]:
        """
        Perform DFS traversal starting from given vertex.
        
        Args:
            start_vertex: Vertex to start DFS from
            
        Returns:
            List of vertices in DFS order
            
        Educational Purpose:
        - Shows depth-first exploration order
        - Demonstrates recursive/stack-based traversal
        - Useful for understanding DFS algorithm
        """
        if start_vertex not in self.vertices:
            raise ValueError(f"Vertex {start_vertex} not in graph")
        
        visited = set()
        traversal_order = []
        
        def dfs_helper(vertex: str):
            visited.add(vertex)
            traversal_order.append(vertex)
            
            for neighbor, _ in self.adjacency_list[vertex]:
                if neighbor not in visited:
                    dfs_helper(neighbor)
        
        dfs_helper(start_vertex)
        return traversal_order
    
    def find_shortest_path_bfs(self, start: str, end: str) -> Optional[List[str]]:
        """
        Find shortest path between two vertices using BFS (unweighted graphs).
        
        Args:
            start: Starting vertex
            end: Destination vertex
            
        Returns:
            List of vertices forming shortest path, or None if no path exists
            
        Educational Purpose:
        - Shows how BFS finds shortest paths in unweighted graphs
        - Demonstrates parent tracking for path reconstruction
        - Useful for understanding why BFS gives shortest paths
        """
        if start not in self.vertices or end not in self.vertices:
            raise ValueError("Start or end vertex not in graph")
        
        if start == end:
            return [start]
        
        # BFS with parent tracking
        visited = set()
        parent = {}
        queue = deque([start])
        visited.add(start)
        
        while queue:
            current_vertex = queue.popleft()
            
            # Check if we reached the destination
            if current_vertex == end:
                # Reconstruct path
                path = []
                vertex = end
                while vertex is not None:
                    path.append(vertex)
                    vertex = parent.get(vertex)
                return path[::-1]  # Reverse to get start -> end
            
            # Explore neighbors
            for neighbor, _ in self.adjacency_list[current_vertex]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    parent[neighbor] = current_vertex
                    queue.append(neighbor)
        
        return None  # No path found
    
    def _dfs_visit(self, vertex: str, visited: Set[str]) -> None:
        """Helper method for DFS traversal."""
        visited.add(vertex)
        for neighbor, _ in self.adjacency_list[vertex]:
            if neighbor not in visited:
                self._dfs_visit(neighbor, visited)
    
    def _bfs_visit(self, start_vertex: str, visited: Set[str]) -> None:
        """
        Helper method for BFS traversal.
        
        Args:
            start_vertex: Starting vertex for BFS
            visited: Set to track visited vertices
            
        Educational Purpose:
        - Demonstrates breadth-first traversal using a queue
        - Shows level-by-level exploration of the graph
        - Useful for finding shortest paths in unweighted graphs
        - Complementary to DFS for different traversal strategies
        
        Time Complexity: O(V + E) where V is vertices, E is edges
        Space Complexity: O(V) for the queue and visited set
        """
        # Initialize queue with starting vertex
        queue = deque([start_vertex])
        visited.add(start_vertex)
        
        # Process vertices level by level
        while queue:
            # Remove vertex from front of queue (FIFO)
            current_vertex = queue.popleft()
            
            # Explore all neighbors of current vertex
            for neighbor, _ in self.adjacency_list[current_vertex]:
                if neighbor not in visited:
                    # Mark neighbor as visited and add to queue
                    visited.add(neighbor)
                    queue.append(neighbor)
    
    def get_adjacency_matrix(self) -> Dict[str, Dict[str, float]]:
        """Get adjacency matrix representation."""
        matrix = {}
        vertices = sorted(self.get_all_vertices())
        
        for u in vertices:
            matrix[u] = {}
            for v in vertices:
                matrix[u][v] = 0 if u == v else float('inf')
        
        for u, v, weight in self.edges:
            matrix[u][v] = weight
            if not self.directed:
                matrix[v][u] = weight
        
        return matrix
    
    def print_adjacency_list(self) -> None:
        """Print the adjacency list representation."""
        print("Adjacency List:")
        for vertex in sorted(self.vertices):
            neighbors = self.adjacency_list[vertex]
            neighbor_str = ", ".join([f"{n}({w})" for n, w in neighbors])
            print(f"  {vertex}: [{neighbor_str}]")
    
    def print_adjacency_matrix(self) -> None:
        """Print the adjacency matrix representation."""
        matrix = self.get_adjacency_matrix()
        vertices = sorted(self.get_all_vertices())
        
        print("Adjacency Matrix:")
        print("   ", end="")
        for v in vertices:
            print(f"{v:>6}", end="")
        print()
        
        for u in vertices:
            print(f"{u}: ", end="")
            for v in vertices:
                if matrix[u][v] == float('inf'):
                    print("   inf", end="")
                else:
                    print(f"{matrix[u][v]:>6.1f}", end="")
            print()
    
    def __str__(self) -> str:
        """String representation of the graph."""
        graph_type = "Directed" if self.directed else "Undirected"
        return f"{graph_type} Graph: {self.vertex_count} vertices, {self.edge_count} edges"
    
    def __repr__(self) -> str:
        """Detailed string representation."""
        return f"Graph(directed={self.directed}, vertices={self.vertex_count}, edges={self.edge_count})"


def create_sample_graphs():
    """Create sample graphs for demonstration."""
    
    # Sample undirected graph
    print("=== Creating Sample Undirected Graph ===")
    undirected_graph = Graph(directed=False)
    undirected_graph.add_edge('A', 'B', 4)
    undirected_graph.add_edge('A', 'C', 2)
    undirected_graph.add_edge('B', 'D', 1)
    undirected_graph.add_edge('C', 'D', 2)
    undirected_graph.add_edge('C', 'E', 3)
    undirected_graph.add_edge('D', 'E', 1)
    
    print(undirected_graph)
    undirected_graph.print_adjacency_list()
    print()
    undirected_graph.print_adjacency_matrix()
    print()
    
    # Sample directed graph
    print("=== Creating Sample Directed Graph ===")
    directed_graph = Graph(directed=True)
    directed_graph.add_edge('A', 'B', 1)
    directed_graph.add_edge('A', 'C', 2)
    directed_graph.add_edge('B', 'D', 3)
    directed_graph.add_edge('C', 'D', 1)
    directed_graph.add_edge('D', 'E', 2)
    directed_graph.add_edge('E', 'A', 1)  # Creates a cycle
    
    print(directed_graph)
    directed_graph.print_adjacency_list()
    print()
    directed_graph.print_adjacency_matrix()
    print()
    
    return undirected_graph, directed_graph


if __name__ == "__main__":
    # Demonstrate the Graph class
    undirected_g, directed_g = create_sample_graphs()
    
    # Test some methods
    print("=== Testing Graph Methods ===")
    print(f"Undirected graph is connected: {undirected_g.is_connected()}")
    print(f"Undirected graph is connected (BFS): {undirected_g.is_connected_bfs()}")
    print(f"Vertex A degree: {undirected_g.get_vertex_degree('A')}")
    print(f"Edge A-B weight: {undirected_g.get_edge_weight('A', 'B')}")
    print(f"Has edge A-B: {undirected_g.has_edge('A', 'B')}")
    print(f"Has edge B-A: {undirected_g.has_edge('B', 'A')}")  # Should be True for undirected
    
    print(f"\nDirected graph vertex A in-degree: {directed_g.get_in_degree('A')}")
    print(f"Directed graph vertex A out-degree: {directed_g.get_vertex_degree('A')}")
    
    # Test BFS and DFS traversals
    print("\n=== Testing BFS and DFS Traversals ===")
    
    # BFS traversal from vertex A
    print("BFS traversal from A:", undirected_g.bfs_traversal('A'))
    
    # DFS traversal from vertex A
    print("DFS traversal from A:", undirected_g.dfs_traversal('A'))
    
    # Find shortest path using BFS
    print("\n=== Testing Shortest Path with BFS ===")
    shortest_path = undirected_g.find_shortest_path_bfs('A', 'E')
    if shortest_path:
        print(f"Shortest path from A to E: {' → '.join(shortest_path)}")
        print(f"Path length: {len(shortest_path) - 1} edges")
    else:
        print("No path found from A to E")
    
    # Test with different start/end points
    shortest_path2 = undirected_g.find_shortest_path_bfs('B', 'D')
    if shortest_path2:
        print(f"Shortest path from B to D: {' → '.join(shortest_path2)}")
        print(f"Path length: {len(shortest_path2) - 1} edges")
    
    # Compare BFS and DFS traversal orders
    print("\n=== Comparing BFS vs DFS Traversal Orders ===")
    print("Graph structure:")
    print("    A --4-- B --1-- D")
    print("    |       |       |")
    print("    2       1       1")
    print("    |       |       |")
    print("    C --2-- D --1-- E")
    
    bfs_order = undirected_g.bfs_traversal('A')
    dfs_order = undirected_g.dfs_traversal('A')
    
    print(f"\nBFS order (level-by-level): {bfs_order}")
    print(f"DFS order (depth-first):    {dfs_order}")
    print("\nNotice how BFS explores neighbors level by level,")
    print("while DFS goes deep into one branch before exploring others.")
