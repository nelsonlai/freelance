"""
Enhanced Graph Representations Implementation
Comprehensive implementation with extensive educational comments

This module demonstrates both adjacency matrix and adjacency list representations
with detailed explanations for educational purposes.
"""

from typing import Dict, List, Set, Optional, Tuple, Union
import sys


class AdjacencyMatrixGraph:
    """
    Graph implementation using adjacency matrix representation.
    
    Adjacency Matrix:
    - 2D array where matrix[i][j] = 1 if edge exists between vertex i and j
    - For weighted graphs, matrix[i][j] = weight of edge (i,j)
    - Space complexity: O(V²) where V is number of vertices
    - Edge lookup: O(1) - direct array access
    - Best for: Dense graphs where most vertices are connected
    
    Educational Notes:
    - Always allocates full V×V matrix even for sparse graphs
    - Wastes space for graphs with few edges
    - Excellent for frequent edge existence queries
    - Used in algorithms requiring matrix operations (Floyd-Warshall)
    """
    
    def __init__(self, vertices: List[str], directed: bool = False, weighted: bool = False):
        """
        Initialize adjacency matrix graph.
        
        Args:
            vertices: List of vertex labels (strings or integers)
            directed: True for directed graph, False for undirected
            weighted: True if edges have weights, False for unweighted
            
        Time Complexity: O(V²) for matrix initialization
        Space Complexity: O(V²) for storing the matrix
        """
        self.vertices = vertices
        self.vertex_count = len(vertices)
        self.directed = directed
        self.weighted = weighted
        
        # Create mapping from vertex to index for O(1) lookup
        self.vertex_to_index = {vertex: i for i, vertex in enumerate(vertices)}
        
        # Initialize adjacency matrix
        # For unweighted graphs: 0 = no edge, 1 = edge exists
        # For weighted graphs: 0 = no edge, weight = edge weight
        # For directed graphs: matrix[i][j] represents edge from i to j
        # For undirected graphs: matrix[i][j] = matrix[j][i] (symmetric)
        infinity = float('inf')
        initial_value = 0 if not weighted else infinity
        
        self.matrix = [[initial_value for _ in range(self.vertex_count)] 
                      for _ in range(self.vertex_count)]
        
        # Set diagonal to 0 (vertices are connected to themselves with weight 0)
        for i in range(self.vertex_count):
            self.matrix[i][i] = 0
    
    def add_edge(self, u: str, v: str, weight: float = 1.0) -> None:
        """
        Add an edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex  
            weight: Edge weight (default 1.0 for unweighted graphs)
            
        Time Complexity: O(1) - direct matrix access
        """
        if u not in self.vertex_to_index or v not in self.vertex_to_index:
            raise ValueError(f"Vertex {u} or {v} not in graph")
        
        u_idx = self.vertex_to_index[u]
        v_idx = self.vertex_to_index[v]
        
        # Add edge from u to v
        if self.weighted:
            self.matrix[u_idx][v_idx] = weight
        else:
            self.matrix[u_idx][v_idx] = 1
        
        # For undirected graphs, add edge from v to u as well
        if not self.directed:
            if self.weighted:
                self.matrix[v_idx][u_idx] = weight
            else:
                self.matrix[v_idx][u_idx] = 1
    
    def remove_edge(self, u: str, v: str) -> None:
        """
        Remove edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Time Complexity: O(1) - direct matrix access
        """
        if u not in self.vertex_to_index or v not in self.vertex_to_index:
            raise ValueError(f"Vertex {u} or {v} not in graph")
        
        u_idx = self.vertex_to_index[u]
        v_idx = self.vertex_to_index[v]
        
        # Remove edge from u to v
        infinity = float('inf') if self.weighted else 0
        self.matrix[u_idx][v_idx] = infinity
        
        # For undirected graphs, remove edge from v to u as well
        if not self.directed:
            self.matrix[v_idx][u_idx] = infinity
    
    def has_edge(self, u: str, v: str) -> bool:
        """
        Check if edge exists between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            True if edge exists, False otherwise
            
        Time Complexity: O(1) - direct matrix access
        """
        if u not in self.vertex_to_index or v not in self.vertex_to_index:
            return False
        
        u_idx = self.vertex_to_index[u]
        v_idx = self.vertex_to_index[v]
        
        if self.weighted:
            return self.matrix[u_idx][v_idx] != float('inf')
        else:
            return self.matrix[u_idx][v_idx] == 1
    
    def get_edge_weight(self, u: str, v: str) -> Optional[float]:
        """
        Get weight of edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            Edge weight if edge exists, None otherwise
            
        Time Complexity: O(1) - direct matrix access
        """
        if not self.has_edge(u, v):
            return None
        
        u_idx = self.vertex_to_index[u]
        v_idx = self.vertex_to_index[v]
        
        weight = self.matrix[u_idx][v_idx]
        return None if weight == float('inf') else weight
    
    def get_neighbors(self, vertex: str) -> List[Tuple[str, float]]:
        """
        Get all neighbors of a vertex with their edge weights.
        
        Args:
            vertex: Vertex to find neighbors for
            
        Returns:
            List of (neighbor, weight) tuples
            
        Time Complexity: O(V) - must check entire row/column
        """
        if vertex not in self.vertex_to_index:
            raise ValueError(f"Vertex {vertex} not in graph")
        
        vertex_idx = self.vertex_to_index[vertex]
        neighbors = []
        
        # Check all vertices for connections
        for i, neighbor in enumerate(self.vertices):
            if i == vertex_idx:  # Skip self-connection
                continue
            
            if self.weighted:
                weight = self.matrix[vertex_idx][i]
                if weight != float('inf'):
                    neighbors.append((neighbor, weight))
            else:
                if self.matrix[vertex_idx][i] == 1:
                    neighbors.append((neighbor, 1.0))
        
        return neighbors
    
    def get_degree(self, vertex: str) -> int:
        """
        Get degree of a vertex (number of incident edges).
        
        Args:
            vertex: Vertex to find degree for
            
        Returns:
            Degree of the vertex
            
        Time Complexity: O(V) - must count neighbors
        """
        return len(self.get_neighbors(vertex))
    
    def print_matrix(self) -> None:
        """
        Print the adjacency matrix in a readable format.
        
        Educational Purpose:
        - Shows the complete graph structure
        - Helps visualize dense vs sparse graphs
        - Useful for debugging and understanding algorithms
        """
        print("Adjacency Matrix:")
        
        # Print header row
        print("   ", end="")
        for vertex in self.vertices:
            print(f"{vertex:>6}", end="")
        print()
        
        # Print each row
        for i, vertex in enumerate(self.vertices):
            print(f"{vertex}: ", end="")
            for j in range(self.vertex_count):
                value = self.matrix[i][j]
                if value == float('inf'):
                    print("   inf", end="")
                elif self.weighted:
                    print(f"{value:>6.1f}", end="")
                else:
                    print(f"{value:>6d}", end="")
            print()
    
    def get_edge_count(self) -> int:
        """
        Count total number of edges in the graph.
        
        Returns:
            Number of edges
            
        Time Complexity: O(V²) - must check entire matrix
        """
        edge_count = 0
        infinity = float('inf') if self.weighted else 0
        
        for i in range(self.vertex_count):
            start_j = i + 1 if not self.directed else 0
            for j in range(start_j, self.vertex_count):
                if i == j:  # Skip diagonal
                    continue
                if self.matrix[i][j] != infinity:
                    edge_count += 1
        
        return edge_count
    
    def __str__(self) -> str:
        """String representation of the graph."""
        graph_type = "Directed" if self.directed else "Undirected"
        weight_type = "Weighted" if self.weighted else "Unweighted"
        return f"{graph_type} {weight_type} Adjacency Matrix Graph: {self.vertex_count} vertices, {self.get_edge_count()} edges"


class AdjacencyListGraph:
    """
    Graph implementation using adjacency list representation.
    
    Adjacency List:
    - Each vertex maintains a list of its neighbors
    - For weighted graphs, store (neighbor, weight) tuples
    - Space complexity: O(V + E) where V is vertices, E is edges
    - Edge lookup: O(degree) - must search neighbor list
    - Best for: Sparse graphs where few vertices are connected
    
    Educational Notes:
    - Space efficient for sparse graphs
    - Fast iteration over neighbors
    - Used in most graph algorithms (BFS, DFS, Dijkstra)
    - Dynamic - easy to add/remove vertices
    """
    
    def __init__(self, directed: bool = False, weighted: bool = False):
        """
        Initialize adjacency list graph.
        
        Args:
            directed: True for directed graph, False for undirected
            weighted: True if edges have weights, False for unweighted
            
        Time Complexity: O(1) - just initialization
        Space Complexity: O(1) - empty graph
        """
        self.adjacency_list: Dict[str, List[Tuple[str, float]]] = {}
        self.vertices: Set[str] = set()
        self.directed = directed
        self.weighted = weighted
        self.edge_count = 0
    
    def add_vertex(self, vertex: str) -> None:
        """
        Add a vertex to the graph.
        
        Args:
            vertex: Vertex label to add
            
        Time Complexity: O(1) - hash table insertion
        """
        if vertex not in self.vertices:
            self.vertices.add(vertex)
            self.adjacency_list[vertex] = []
    
    def add_edge(self, u: str, v: str, weight: float = 1.0) -> None:
        """
        Add an edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            weight: Edge weight (default 1.0 for unweighted graphs)
            
        Time Complexity: O(1) - append to list
        """
        # Add vertices if they don't exist
        self.add_vertex(u)
        self.add_vertex(v)
        
        # Add edge from u to v
        self.adjacency_list[u].append((v, weight))
        self.edge_count += 1
        
        # For undirected graphs, add edge from v to u as well
        if not self.directed:
            self.adjacency_list[v].append((u, weight))
    
    def remove_edge(self, u: str, v: str) -> bool:
        """
        Remove edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            True if edge was removed, False if edge didn't exist
            
        Time Complexity: O(degree) - must search neighbor list
        """
        if u not in self.adjacency_list or v not in self.adjacency_list:
            return False
        
        # Remove edge from u to v
        removed = False
        for i, (neighbor, weight) in enumerate(self.adjacency_list[u]):
            if neighbor == v:
                del self.adjacency_list[u][i]
                removed = True
                self.edge_count -= 1
                break
        
        # For undirected graphs, remove edge from v to u as well
        if not self.directed and removed:
            for i, (neighbor, weight) in enumerate(self.adjacency_list[v]):
                if neighbor == u:
                    del self.adjacency_list[v][i]
                    break
        
        return removed
    
    def has_edge(self, u: str, v: str) -> bool:
        """
        Check if edge exists between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            True if edge exists, False otherwise
            
        Time Complexity: O(degree) - must search neighbor list
        """
        if u not in self.adjacency_list:
            return False
        
        for neighbor, weight in self.adjacency_list[u]:
            if neighbor == v:
                return True
        
        return False
    
    def get_edge_weight(self, u: str, v: str) -> Optional[float]:
        """
        Get weight of edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            Edge weight if edge exists, None otherwise
            
        Time Complexity: O(degree) - must search neighbor list
        """
        if u not in self.adjacency_list:
            return None
        
        for neighbor, weight in self.adjacency_list[u]:
            if neighbor == v:
                return weight
        
        return None
    
    def get_neighbors(self, vertex: str) -> List[Tuple[str, float]]:
        """
        Get all neighbors of a vertex with their edge weights.
        
        Args:
            vertex: Vertex to find neighbors for
            
        Returns:
            List of (neighbor, weight) tuples
            
        Time Complexity: O(degree) - return the list directly
        """
        if vertex not in self.adjacency_list:
            return []
        
        return self.adjacency_list[vertex].copy()
    
    def get_degree(self, vertex: str) -> int:
        """
        Get degree of a vertex (number of incident edges).
        
        Args:
            vertex: Vertex to find degree for
            
        Returns:
            Degree of the vertex
            
        Time Complexity: O(1) - just return list length
        """
        if vertex not in self.adjacency_list:
            return 0
        
        return len(self.adjacency_list[vertex])
    
    def get_in_degree(self, vertex: str) -> int:
        """
        Get in-degree of a vertex (number of incoming edges).
        Only meaningful for directed graphs.
        
        Args:
            vertex: Vertex to find in-degree for
            
        Returns:
            In-degree of the vertex
            
        Time Complexity: O(V + E) - must check all edges
        """
        in_degree = 0
        
        for v in self.adjacency_list:
            for neighbor, weight in self.adjacency_list[v]:
                if neighbor == vertex:
                    in_degree += 1
        
        return in_degree
    
    def print_adjacency_list(self) -> None:
        """
        Print the adjacency list in a readable format.
        
        Educational Purpose:
        - Shows the sparse structure clearly
        - Easy to see which vertices are connected
        - Useful for understanding graph algorithms
        """
        print("Adjacency List:")
        
        for vertex in sorted(self.vertices):
            if vertex in self.adjacency_list:
                neighbors = self.adjacency_list[vertex]
                if self.weighted:
                    neighbor_str = ", ".join([f"{n}({w})" for n, w in neighbors])
                else:
                    neighbor_str = ", ".join([f"{n}" for n, w in neighbors])
                print(f"  {vertex}: [{neighbor_str}]")
            else:
                print(f"  {vertex}: []")
    
    def __str__(self) -> str:
        """String representation of the graph."""
        graph_type = "Directed" if self.directed else "Undirected"
        weight_type = "Weighted" if self.weighted else "Unweighted"
        return f"{graph_type} {weight_type} Adjacency List Graph: {len(self.vertices)} vertices, {self.edge_count} edges"


def demonstrate_representations():
    """
    Comprehensive demonstration of both graph representations.
    
    Educational Purpose:
    - Shows when to use each representation
    - Demonstrates space/time trade-offs
    - Provides hands-on experience with both approaches
    """
    
    print("=" * 70)
    print("GRAPH REPRESENTATIONS COMPREHENSIVE DEMONSTRATION")
    print("=" * 70)
    
    # Example 1: Small graph comparison
    print("\n1. Small Graph Comparison")
    print("-" * 35)
    
    vertices = ['A', 'B', 'C', 'D']
    edges = [('A', 'B', 3), ('A', 'C', 1), ('B', 'C', 2), ('C', 'D', 4)]
    
    print("Graph:")
    print("    A --3-- B")
    print("    |       |")
    print("    1       2")
    print("    |       |")
    print("    C --4-- D")
    
    # Adjacency Matrix Implementation
    print("\nAdjacency Matrix Implementation:")
    print("-" * 40)
    matrix_graph = AdjacencyMatrixGraph(vertices, directed=False, weighted=True)
    
    for u, v, weight in edges:
        matrix_graph.add_edge(u, v, weight)
    
    print(matrix_graph)
    matrix_graph.print_matrix()
    print(f"Space used: O(V²) = O({len(vertices)}²) = {len(vertices)**2} cells")
    
    # Adjacency List Implementation
    print("\nAdjacency List Implementation:")
    print("-" * 40)
    list_graph = AdjacencyListGraph(directed=False, weighted=True)
    
    for u, v, weight in edges:
        list_graph.add_edge(u, v, weight)
    
    print(list_graph)
    list_graph.print_adjacency_list()
    print(f"Space used: O(V + E) = O({len(vertices)} + {len(edges)}) = {len(vertices) + len(edges)} elements")
    
    # Example 2: Performance comparison
    print("\n2. Performance Comparison")
    print("-" * 35)
    
    print("Operations on the same graph:")
    
    # Edge existence check
    print(f"Has edge A-B: Matrix={matrix_graph.has_edge('A', 'B')}, List={list_graph.has_edge('A', 'B')}")
    print(f"Has edge A-D: Matrix={matrix_graph.has_edge('A', 'D')}, List={list_graph.has_edge('A', 'D')}")
    
    # Edge weight lookup
    print(f"Weight A-B: Matrix={matrix_graph.get_edge_weight('A', 'B')}, List={list_graph.get_edge_weight('A', 'B')}")
    
    # Neighbor listing
    print(f"Neighbors of A: Matrix={matrix_graph.get_neighbors('A')}, List={list_graph.get_neighbors('A')}")
    
    # Example 3: When to use which representation
    print("\n3. When to Use Which Representation")
    print("-" * 45)
    
    print("Use Adjacency Matrix when:")
    print("  - Graph is dense (many edges)")
    print("  - Frequent edge existence queries")
    print("  - Matrix operations needed (Floyd-Warshall)")
    print("  - Small graphs where memory isn't a concern")
    
    print("\nUse Adjacency List when:")
    print("  - Graph is sparse (few edges)")
    print("  - Frequent neighbor iteration")
    print("  - Dynamic graph (adding/removing vertices)")
    print("  - Memory efficiency is important")
    
    # Example 4: Real-world scenarios
    print("\n4. Real-World Scenarios")
    print("-" * 30)
    
    print("Social Network (Facebook):")
    print("  - Sparse graph (users have few friends)")
    print("  - Frequent neighbor iteration (show friends)")
    print("  - Recommendation: Adjacency List")
    
    print("\nRoad Network (Google Maps):")
    print("  - Sparse graph (cities connect to few others)")
    print("  - Frequent neighbor iteration (find routes)")
    print("  - Recommendation: Adjacency List")
    
    print("\nComplete Tournament:")
    print("  - Dense graph (every team plays every other)")
    print("  - Frequent edge queries (who played whom?)")
    print("  - Recommendation: Adjacency Matrix")
    
    # Example 5: Space complexity analysis
    print("\n5. Space Complexity Analysis")
    print("-" * 35)
    
    print("For a graph with V vertices and E edges:")
    print(f"  Adjacency Matrix: O(V²) = {len(vertices)}² = {len(vertices)**2} cells")
    print(f"  Adjacency List: O(V + E) = {len(vertices)} + {len(edges)} = {len(vertices) + len(edges)} elements")
    
    print(f"\nBreak-even point: V² = V + E")
    print(f"For {len(vertices)} vertices: {len(vertices)**2} = {len(vertices)} + E")
    print(f"E = {len(vertices)**2 - len(vertices)}")
    print(f"When E > {len(vertices)**2 - len(vertices)}, matrix uses more space")


if __name__ == "__main__":
    demonstrate_representations()
