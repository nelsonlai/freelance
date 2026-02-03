"""
Enhanced Lecture Implementation - Comprehensive Graph Algorithms
Complete implementation of all algorithms from the enhanced lecture with extensive educational comments

This module serves as the main implementation for the enhanced graph algorithms lecture,
providing comprehensive, well-commented code for all major graph algorithms covered.
"""

import heapq
import time
from collections import deque, defaultdict
from typing import Dict, List, Set, Tuple, Optional, Any, Union
from enum import Enum


class VertexColor(Enum):
    """
    Three-color system for DFS and cycle detection algorithms.
    
    Educational Purpose:
    - WHITE: Unvisited vertex (initial state)
    - GRAY: Currently being processed (discovered but not finished)
    - BLACK: Completely processed (finished)
    
    This system is crucial for:
    - Cycle detection in directed graphs
    - Understanding DFS execution order
    - Implementing topological sorting
    - Finding strongly connected components
    """
    WHITE = "WHITE"
    GRAY = "GRAY"
    BLACK = "BLACK"


class GraphType(Enum):
    """Enumeration for different graph types."""
    DIRECTED = "DIRECTED"
    UNDIRECTED = "UNDIRECTED"


class WeightType(Enum):
    """Enumeration for weight types."""
    UNWEIGHTED = "UNWEIGHTED"
    WEIGHTED = "WEIGHTED"


class ComprehensiveGraph:
    """
    Comprehensive graph implementation supporting all major graph algorithms.
    
    Educational Goals:
    1. Provide a unified interface for all graph operations
    2. Support both directed and undirected graphs
    3. Handle both weighted and unweighted edges
    4. Include comprehensive error checking and validation
    5. Provide detailed logging for educational purposes
    6. Support all major graph algorithms in one class
    
    Design Decisions:
    - Uses adjacency list representation for efficiency
    - Supports dynamic vertex/edge addition and removal
    - Maintains multiple data structures for different algorithms
    - Includes extensive validation and error checking
    """
    
    def __init__(self, directed: bool = False, weighted: bool = False, debug: bool = False):
        """
        Initialize comprehensive graph.
        
        Args:
            directed: True for directed graph, False for undirected
            weighted: True if edges have weights, False for unweighted
            debug: True to enable detailed logging for educational purposes
            
        Time Complexity: O(1) - just initialization
        Space Complexity: O(1) - empty graph
        """
        self.directed = directed
        self.weighted = weighted
        self.debug = debug
        
        # Core graph representation
        self.adjacency_list: Dict[str, List[Tuple[str, float]]] = defaultdict(list)
        self.vertices: Set[str] = set()
        self.edges: List[Tuple[str, str, float]] = []
        
        # Algorithm-specific data structures
        self.in_degree: Dict[str, int] = defaultdict(int)
        self.out_degree: Dict[str, int] = defaultdict(int)
        
        # Statistics
        self.vertex_count = 0
        self.edge_count = 0
        
        if self.debug:
            print(f"Initialized {self._get_graph_type()} graph with debug mode enabled")
    
    def _get_graph_type(self) -> str:
        """Get human-readable graph type description."""
        directed_str = "directed" if self.directed else "undirected"
        weighted_str = "weighted" if self.weighted else "unweighted"
        return f"{directed_str} {weighted_str}"
    
    def add_vertex(self, vertex: str) -> None:
        """
        Add a vertex to the graph.
        
        Args:
            vertex: Vertex label to add
            
        Time Complexity: O(1) - hash set insertion
        Space Complexity: O(1) - single vertex addition
        
        Educational Notes:
        - Vertices can be added dynamically
        - Duplicate additions are ignored
        - Vertex labels can be any hashable type (strings, integers, etc.)
        """
        if vertex not in self.vertices:
            self.vertices.add(vertex)
            self.vertex_count += 1
            self.in_degree[vertex] = 0
            self.out_degree[vertex] = 0
            
            if self.debug:
                print(f"Added vertex: {vertex}")
    
    def add_edge(self, u: str, v: str, weight: float = 1.0) -> None:
        """
        Add an edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            weight: Edge weight (default 1.0 for unweighted graphs)
            
        Time Complexity: O(1) - list append operation
        Space Complexity: O(1) - single edge addition
        
        Educational Notes:
        - Automatically adds vertices if they don't exist
        - For undirected graphs, adds edge in both directions
        - Maintains degree counts for efficient algorithm implementations
        - Validates weight for weighted graphs
        """
        # Validate weight for weighted graphs
        if self.weighted and weight <= 0:
            raise ValueError(f"Weight must be positive for weighted graphs, got: {weight}")
        
        # Add vertices if they don't exist
        self.add_vertex(u)
        self.add_vertex(v)
        
        # Add edge from u to v
        self.adjacency_list[u].append((v, weight))
        self.edges.append((u, v, weight))
        self.edge_count += 1
        self.out_degree[u] += 1
        self.in_degree[v] += 1
        
        # For undirected graphs, add edge from v to u as well
        if not self.directed:
            self.adjacency_list[v].append((u, weight))
            self.out_degree[v] += 1
            self.in_degree[u] += 1
        
        if self.debug:
            direction = "→" if self.directed else "↔"
            print(f"Added edge: {u} {direction} {v} (weight: {weight})")
    
    def remove_edge(self, u: str, v: str) -> bool:
        """
        Remove edge between vertices u and v.
        
        Args:
            u: Source vertex
            v: Destination vertex
            
        Returns:
            True if edge was removed, False if edge didn't exist
            
        Time Complexity: O(degree) - must search neighbor list
        Space Complexity: O(1) - no additional space needed
        """
        if u not in self.adjacency_list:
            return False
        
        # Remove edge from u to v
        removed = False
        for i, (neighbor, weight) in enumerate(self.adjacency_list[u]):
            if neighbor == v:
                del self.adjacency_list[u][i]
                self.edge_count -= 1
                self.out_degree[u] -= 1
                self.in_degree[v] -= 1
                removed = True
                break
        
        # For undirected graphs, remove edge from v to u as well
        if not self.directed and removed and v in self.adjacency_list:
            for i, (neighbor, weight) in enumerate(self.adjacency_list[v]):
                if neighbor == u:
                    del self.adjacency_list[v][i]
                    self.out_degree[v] -= 1
                    self.in_degree[u] -= 1
                    break
        
        if self.debug and removed:
            direction = "→" if self.directed else "↔"
            print(f"Removed edge: {u} {direction} {v}")
        
        return removed
    
    def get_neighbors(self, vertex: str) -> List[Tuple[str, float]]:
        """
        Get all neighbors of a vertex with their edge weights.
        
        Args:
            vertex: Vertex to find neighbors for
            
        Returns:
            List of (neighbor, weight) tuples
            
        Time Complexity: O(degree) - return the list directly
        Space Complexity: O(degree) - copy of neighbor list
        """
        if vertex not in self.adjacency_list:
            return []
        
        return self.adjacency_list[vertex].copy()
    
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
    
    def print_graph(self) -> None:
        """
        Print the graph in a readable format.
        
        Educational Purpose:
        - Shows the complete graph structure
        - Helps visualize dense vs sparse graphs
        - Useful for debugging and understanding algorithms
        - Displays both adjacency list and edge list
        """
        print(f"\n{self._get_graph_type().title()} Graph Representation:")
        print("=" * 50)
        
        # Print adjacency list
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
        
        # Print edge list
        print(f"\nEdge List ({len(self.edges)} edges):")
        for u, v, weight in self.edges:
            direction = "→" if self.directed else "↔"
            if self.weighted:
                print(f"  {u} {direction} {v} (weight: {weight})")
            else:
                print(f"  {u} {direction} {v}")
        
        # Print graph statistics
        print(f"\nGraph Statistics:")
        print(f"  Vertices: {self.vertex_count}")
        print(f"  Edges: {self.edge_count}")
        print(f"  Type: {self._get_graph_type()}")
    
    def breadth_first_search(self, start: str, target: Optional[str] = None) -> Dict[str, Any]:
        """
        Breadth-First Search implementation with comprehensive tracking.
        
        BFS Algorithm:
        1. Start from source vertex
        2. Visit all neighbors at distance 1
        3. Visit all neighbors at distance 2
        4. Continue until all reachable vertices visited
        
        Real-World Applications:
        - Social network analysis (degrees of separation)
        - Web crawling (level-by-level page discovery)
        - GPS navigation (shortest path in unweighted graphs)
        - Network broadcasting (information propagation)
        - Game AI (finding shortest moves)
        
        Args:
            start: Starting vertex for BFS
            target: Optional target vertex to search for
            
        Returns:
            Dictionary containing comprehensive BFS results
            
        Time Complexity: O(V + E) where V is vertices, E is edges
        Space Complexity: O(V) for queue and visited tracking
        """
        if self.debug:
            print(f"\nBreadth-First Search starting from: {start}")
            if target:
                print(f"Searching for target: {target}")
        
        start_time = time.time()
        
        # Initialize data structures
        visited = set()
        queue = deque([start])
        visited.add(start)
        
        # Results tracking
        traversal_order = [start]
        distances = {start: 0}
        parents = {start: None}
        levels = {0: [start]}
        current_level = 0
        
        if self.debug:
            print(f"Level {current_level}: {levels[current_level]}")
        
        # BFS main loop
        while queue:
            current_vertex = queue.popleft()
            current_distance = distances[current_vertex]
            
            if self.debug:
                print(f"Processing: {current_vertex} (distance: {current_distance})")
            
            # Check if we found the target
            if target and current_vertex == target:
                if self.debug:
                    print(f"🎯 Target {target} found at distance {current_distance}!")
                break
            
            # Explore neighbors
            neighbors_added = []
            for neighbor, weight in self.get_neighbors(current_vertex):
                if neighbor not in visited:
                    # Discover new vertex
                    visited.add(neighbor)
                    queue.append(neighbor)
                    distances[neighbor] = current_distance + 1
                    parents[neighbor] = current_vertex
                    traversal_order.append(neighbor)
                    neighbors_added.append(neighbor)
                    
                    if self.debug:
                        print(f"  → Discovered {neighbor} at distance {current_distance + 1}")
            
            # Update levels for visualization
            if neighbors_added:
                next_level = current_distance + 1
                if next_level not in levels:
                    levels[next_level] = []
                levels[next_level].extend(neighbors_added)
                if self.debug:
                    print(f"  Level {next_level}: {levels[next_level]}")
        
        execution_time = time.time() - start_time
        
        # Prepare comprehensive results
        result = {
            'algorithm': 'BFS',
            'start_vertex': start,
            'target_vertex': target,
            'traversal_order': traversal_order,
            'distances': distances,
            'parents': parents,
            'levels': levels,
            'target_found': target in visited if target else None,
            'execution_time': execution_time,
            'vertices_visited': len(visited),
            'total_vertices': len(self.vertices)
        }
        
        if self.debug:
            print(f"\nBFS Summary:")
            print(f"  Vertices visited: {result['vertices_visited']}/{result['total_vertices']}")
            print(f"  Execution time: {execution_time:.6f} seconds")
            print(f"  Traversal order: {traversal_order}")
        
        return result
    
    def depth_first_search(self, start: str, target: Optional[str] = None) -> Dict[str, Any]:
        """
        Depth-First Search implementation with comprehensive tracking.
        
        DFS Algorithm:
        1. Start from source vertex
        2. Visit first unvisited neighbor
        3. Recursively explore from that neighbor
        4. Backtrack when no more unvisited neighbors
        
        Real-World Applications:
        - Maze solving and pathfinding
        - Cycle detection in directed graphs
        - Topological sorting
        - Finding strongly connected components
        - Dependency resolution (build systems)
        - Game tree exploration (chess, tic-tac-toe)
        - Web crawling (following links deeply)
        
        Args:
            start: Starting vertex for DFS
            target: Optional target vertex to search for
            
        Returns:
            Dictionary containing comprehensive DFS results
            
        Time Complexity: O(V + E) where V is vertices, E is edges
        Space Complexity: O(V) for recursion stack and tracking
        """
        if self.debug:
            print(f"\nDepth-First Search starting from: {start}")
            if target:
                print(f"Searching for target: {target}")
        
        start_time = time.time()
        
        # Initialize tracking variables
        color = {vertex: VertexColor.WHITE for vertex in self.vertices}
        discovery_time = {}
        finish_time = {}
        parents = {}
        traversal_order = []
        tree_edges = []
        back_edges = []
        forward_edges = []
        cross_edges = []
        time_counter = 0
        
        def dfs_visit(vertex: str, parent: Optional[str] = None) -> bool:
            """
            Recursive DFS visit function with comprehensive edge classification.
            
            Args:
                vertex: Current vertex being visited
                parent: Parent vertex in DFS tree
                
            Returns:
                True if target was found, False otherwise
            """
            nonlocal time_counter
            
            # Mark vertex as discovered
            time_counter += 1
            discovery_time[vertex] = time_counter
            color[vertex] = VertexColor.GRAY
            parents[vertex] = parent
            traversal_order.append(vertex)
            
            if self.debug:
                print(f"  Discovering {vertex} at time {time_counter}")
            
            # Check if we found the target
            if target and vertex == target:
                if self.debug:
                    print(f"🎯 Target {target} found!")
                return True
            
            # Explore neighbors
            for neighbor, weight in self.get_neighbors(vertex):
                if color[neighbor] == VertexColor.WHITE:
                    # Tree edge - exploring new vertex
                    tree_edges.append((vertex, neighbor))
                    if self.debug:
                        print(f"    Tree edge: {vertex} → {neighbor}")
                    if dfs_visit(neighbor, vertex):
                        return True
                elif color[neighbor] == VertexColor.GRAY:
                    # Back edge - cycle detected in directed graphs
                    back_edges.append((vertex, neighbor))
                    if self.debug:
                        print(f"    Back edge: {vertex} → {neighbor} (cycle detected!)")
                else:
                    # Forward or cross edge
                    if discovery_time[vertex] < discovery_time[neighbor]:
                        forward_edges.append((vertex, neighbor))
                        if self.debug:
                            print(f"    Forward edge: {vertex} → {neighbor}")
                    else:
                        cross_edges.append((vertex, neighbor))
                        if self.debug:
                            print(f"    Cross edge: {vertex} → {neighbor}")
            
            # Mark vertex as finished
            time_counter += 1
            finish_time[vertex] = time_counter
            color[vertex] = VertexColor.BLACK
            
            if self.debug:
                print(f"  Finishing {vertex} at time {time_counter}")
            return False
        
        # Start DFS from specified vertex
        target_found = dfs_visit(start)
        
        # Visit any remaining unvisited vertices (for disconnected graphs)
        for vertex in self.vertices:
            if color[vertex] == VertexColor.WHITE:
                if self.debug:
                    print(f"\nStarting DFS from disconnected vertex: {vertex}")
                if dfs_visit(vertex):
                    target_found = True
        
        execution_time = time.time() - start_time
        
        # Prepare comprehensive results
        result = {
            'algorithm': 'DFS',
            'start_vertex': start,
            'target_vertex': target,
            'traversal_order': traversal_order,
            'discovery_time': discovery_time,
            'finish_time': finish_time,
            'parents': parents,
            'target_found': target_found,
            'execution_time': execution_time,
            'tree_edges': tree_edges,
            'back_edges': back_edges,
            'forward_edges': forward_edges,
            'cross_edges': cross_edges,
            'vertices_visited': len(traversal_order),
            'total_vertices': len(self.vertices)
        }
        
        if self.debug:
            print(f"\nDFS Summary:")
            print(f"  Vertices visited: {result['vertices_visited']}/{result['total_vertices']}")
            print(f"  Execution time: {execution_time:.6f} seconds")
            print(f"  Tree edges: {tree_edges}")
            if back_edges:
                print(f"  Back edges (cycles): {back_edges}")
        
        return result
    
    def dijkstra_shortest_path(self, start: str) -> Dict[str, Any]:
        """
        Dijkstra's algorithm for single-source shortest paths.
        
        Algorithm:
        1. Initialize distances: dist[start] = 0, others = infinity
        2. Use priority queue to process vertices by distance
        3. For each vertex, relax all outgoing edges
        4. Continue until all vertices processed
        
        Real-World Applications:
        - GPS navigation systems
        - Network routing protocols
        - Social network analysis (influence propagation)
        - Game AI (pathfinding with costs)
        - Resource allocation optimization
        
        Args:
            start: Source vertex for shortest paths
            
        Returns:
            Dictionary containing shortest path results
            
        Time Complexity: O((V + E) log V) with binary heap
        Space Complexity: O(V) for priority queue and distances
        """
        if self.debug:
            print(f"\nDijkstra's Algorithm starting from: {start}")
        
        start_time = time.time()
        
        # Initialize distances and previous vertices
        distances = {vertex: float('infinity') for vertex in self.vertices}
        previous = {vertex: None for vertex in self.vertices}
        distances[start] = 0
        
        # Priority queue: (distance, vertex)
        pq = [(0, start)]
        visited = set()
        
        if self.debug:
            print("Step-by-step execution:")
        
        step = 1
        while pq:
            current_distance, current_vertex = heapq.heappop(pq)
            
            if current_vertex in visited:
                continue
            
            visited.add(current_vertex)
            
            if self.debug:
                print(f"  Step {step}: Processing {current_vertex} (distance: {current_distance})")
            
            # Relax all edges from current vertex
            for neighbor, weight in self.get_neighbors(current_vertex):
                if neighbor in visited:
                    continue
                
                new_distance = current_distance + weight
                
                if new_distance < distances[neighbor]:
                    old_distance = distances[neighbor]
                    distances[neighbor] = new_distance
                    previous[neighbor] = current_vertex
                    heapq.heappush(pq, (new_distance, neighbor))
                    
                    if self.debug:
                        print(f"    Updated distance to {neighbor}: {old_distance} → {new_distance}")
            
            step += 1
        
        execution_time = time.time() - start_time
        
        # Prepare results
        result = {
            'algorithm': 'Dijkstra',
            'start_vertex': start,
            'distances': distances,
            'previous': previous,
            'execution_time': execution_time,
            'vertices_processed': len(visited)
        }
        
        if self.debug:
            print(f"\nDijkstra Summary:")
            print(f"  Final distances: {distances}")
            print(f"  Execution time: {execution_time:.6f} seconds")
        
        return result
    
    def topological_sort(self) -> Dict[str, Any]:
        """
        Topological sorting using Kahn's algorithm.
        
        Algorithm:
        1. Calculate in-degree for each vertex
        2. Add vertices with in-degree 0 to queue
        3. Process vertices, decreasing in-degrees of neighbors
        4. Add neighbors with in-degree 0 to queue
        5. Check for cycles
        
        Real-World Applications:
        - Course prerequisite scheduling
        - Build system dependency resolution
        - Task scheduling with dependencies
        - Package installation order
        - Project management (critical path)
        
        Returns:
            Dictionary containing topological sort results
            
        Time Complexity: O(V + E)
        Space Complexity: O(V) for queue and in-degree tracking
        """
        if self.debug:
            print("\nTopological Sort using Kahn's Algorithm")
        
        if not self.directed:
            raise ValueError("Topological sort only works on directed graphs")
        
        start_time = time.time()
        
        # Calculate in-degrees
        in_degree = self.in_degree.copy()
        
        if self.debug:
            print(f"In-degrees: {dict(in_degree)}")
        
        # Initialize queue with vertices of in-degree 0
        queue = deque([v for v, degree in in_degree.items() if degree == 0])
        
        if self.debug:
            print(f"Initial queue (in-degree 0): {list(queue)}")
        
        topological_order = []
        step = 1
        
        # Process vertices
        while queue:
            current_vertex = queue.popleft()
            topological_order.append(current_vertex)
            
            if self.debug:
                print(f"\nStep {step}: Processing {current_vertex}")
                print(f"  Current order: {topological_order}")
            
            # Process all outgoing edges
            for neighbor, weight in self.get_neighbors(current_vertex):
                in_degree[neighbor] -= 1
                
                if self.debug:
                    print(f"  Decreased in-degree of {neighbor}: {in_degree[neighbor] + 1} → {in_degree[neighbor]}")
                
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
                    
                    if self.debug:
                        print(f"  Added {neighbor} to queue")
            
            step += 1
        
        # Check for cycle
        has_cycle = len(topological_order) != len(self.vertices)
        
        execution_time = time.time() - start_time
        
        # Prepare results
        result = {
            'algorithm': 'Topological Sort (Kahn)',
            'topological_order': topological_order,
            'has_cycle': has_cycle,
            'execution_time': execution_time
        }
        
        if self.debug:
            if has_cycle:
                print(f"\nCycle detected! Only {len(topological_order)} vertices processed out of {len(self.vertices)}")
            else:
                print(f"\nTopological sort completed successfully!")
                print(f"Order: {' → '.join(topological_order)}")
        
        return result
    
    def minimum_spanning_tree_kruskal(self) -> Dict[str, Any]:
        """
        Kruskal's algorithm for minimum spanning tree.
        
        Algorithm:
        1. Sort all edges by weight
        2. Use Union-Find data structure
        3. Process edges in order of increasing weight
        4. Add edge if it doesn't create cycle
        
        Real-World Applications:
        - Network design (minimum cost connections)
        - Clustering algorithms
        - Approximation for traveling salesman problem
        - Power grid optimization
        - Transportation network planning
        
        Returns:
            Dictionary containing MST results
            
        Time Complexity: O(E log E) = O(E log V)
        Space Complexity: O(V) for Union-Find
        """
        if self.debug:
            print("\nKruskal's Algorithm for Minimum Spanning Tree")
        
        if self.directed:
            raise ValueError("MST algorithms only work on undirected graphs")
        
        start_time = time.time()
        
        # Union-Find data structure
        class UnionFind:
            def __init__(self, vertices):
                self.parent = {v: v for v in vertices}
                self.rank = {v: 0 for v in vertices}
            
            def find(self, x):
                if self.parent[x] != x:
                    self.parent[x] = self.find(self.parent[x])
                return self.parent[x]
            
            def union(self, x, y):
                px, py = self.find(x), self.find(y)
                if px == py:
                    return False
                
                if self.rank[px] < self.rank[py]:
                    self.parent[px] = py
                elif self.rank[px] > self.rank[py]:
                    self.parent[py] = px
                else:
                    self.parent[py] = px
                    self.rank[px] += 1
                return True
        
        # Sort edges by weight
        sorted_edges = sorted(self.edges, key=lambda x: x[2])
        
        if self.debug:
            print(f"Edges sorted by weight: {sorted_edges}")
        
        # Initialize Union-Find
        uf = UnionFind(list(self.vertices))
        mst_edges = []
        total_weight = 0
        
        if self.debug:
            print("\nProcessing edges:")
        
        # Process edges
        for i, (u, v, weight) in enumerate(sorted_edges):
            if self.debug:
                print(f"  Edge {i+1}: ({u}, {v}) weight {weight}")
            
            if uf.union(u, v):
                mst_edges.append((u, v, weight))
                total_weight += weight
                
                if self.debug:
                    print(f"    ✓ Added to MST")
            else:
                if self.debug:
                    print(f"    ✗ Skipped (would create cycle)")
            
            # Stop if we have V-1 edges
            if len(mst_edges) == len(self.vertices) - 1:
                if self.debug:
                    print(f"    MST complete with {len(mst_edges)} edges")
                break
        
        execution_time = time.time() - start_time
        
        # Prepare results
        result = {
            'algorithm': 'Kruskal MST',
            'mst_edges': mst_edges,
            'total_weight': total_weight,
            'execution_time': execution_time
        }
        
        if self.debug:
            print(f"\nKruskal MST Summary:")
            print(f"  MST edges: {mst_edges}")
            print(f"  Total weight: {total_weight}")
            print(f"  Execution time: {execution_time:.6f} seconds")
        
        return result
    
    def find_shortest_path(self, start: str, end: str, use_dijkstra: bool = True) -> Optional[List[str]]:
        """
        Find shortest path between two vertices.
        
        Args:
            start: Starting vertex
            end: Destination vertex
            use_dijkstra: True for Dijkstra (weighted), False for BFS (unweighted)
            
        Returns:
            List of vertices forming the shortest path, or None if no path exists
        """
        if use_dijkstra and self.weighted:
            result = self.dijkstra_shortest_path(start)
            distances = result['distances']
            previous = result['previous']
            
            if distances[end] == float('infinity'):
                if self.debug:
                    print(f"No path found from {start} to {end}")
                return None
        else:
            result = self.breadth_first_search(start, end)
            distances = result['distances']
            previous = result['parents']
            
            if end not in previous:
                if self.debug:
                    print(f"No path found from {start} to {end}")
                return None
        
        # Reconstruct path
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = previous[current]
        
        path.reverse()
        
        if self.debug:
            algorithm = "Dijkstra" if use_dijkstra else "BFS"
            print(f"{algorithm} Path from {start} to {end}: {' → '.join(path)}")
            if use_dijkstra:
                print(f"Path weight: {distances[end]}")
            else:
                print(f"Path length: {len(path) - 1} edges")
        
        return path
    
    def detect_cycle(self) -> bool:
        """
        Detect cycles in the graph using DFS.
        
        Returns:
            True if cycle exists, False otherwise
        """
        if self.directed:
            return self._detect_cycle_directed()
        else:
            return self._detect_cycle_undirected()
    
    def _detect_cycle_directed(self) -> bool:
        """Detect cycles in directed graphs using DFS with three-color system."""
        if self.debug:
            print("\nCycle Detection in Directed Graph using DFS")
        
        color = {vertex: VertexColor.WHITE for vertex in self.vertices}
        
        def has_cycle_visit(vertex: str) -> bool:
            color[vertex] = VertexColor.GRAY
            
            if self.debug:
                print(f"  Processing {vertex} (GRAY)")
            
            for neighbor, weight in self.get_neighbors(vertex):
                if color[neighbor] == VertexColor.GRAY:
                    if self.debug:
                        print(f"    Back edge to {neighbor} detected - CYCLE FOUND!")
                    return True
                elif color[neighbor] == VertexColor.WHITE:
                    if has_cycle_visit(neighbor):
                        return True
            
            color[vertex] = VertexColor.BLACK
            
            if self.debug:
                print(f"  Finished {vertex} (BLACK)")
            
            return False
        
        # Check all vertices (for disconnected graphs)
        for vertex in self.vertices:
            if color[vertex] == VertexColor.WHITE:
                if self.debug:
                    print(f"Starting cycle detection from {vertex}")
                if has_cycle_visit(vertex):
                    return True
        
        if self.debug:
            print("No cycles detected")
        
        return False
    
    def _detect_cycle_undirected(self) -> bool:
        """Detect cycles in undirected graphs using DFS with parent tracking."""
        if self.debug:
            print("\nCycle Detection in Undirected Graph using DFS")
        
        visited = set()
        
        def has_cycle_visit(vertex: str, parent: Optional[str] = None) -> bool:
            visited.add(vertex)
            
            if self.debug:
                print(f"  Processing {vertex}")
            
            for neighbor, weight in self.get_neighbors(vertex):
                if neighbor not in visited:
                    if has_cycle_visit(neighbor, vertex):
                        return True
                elif neighbor != parent:
                    if self.debug:
                        print(f"    Back edge to {neighbor} detected - CYCLE FOUND!")
                    return True
            
            return False
        
        # Check all vertices (for disconnected graphs)
        for vertex in self.vertices:
            if vertex not in visited:
                if self.debug:
                    print(f"Starting cycle detection from {vertex}")
                if has_cycle_visit(vertex):
                    return True
        
        if self.debug:
            print("No cycles detected")
        
        return False


def demonstrate_comprehensive_algorithms():
    """
    Comprehensive demonstration of all graph algorithms.
    
    Educational Goals:
    1. Show practical applications of all algorithms
    2. Demonstrate when to use each algorithm
    3. Provide hands-on experience with graph algorithms
    4. Show debugging and visualization techniques
    5. Compare algorithm performance and results
    """
    
    print("=" * 80)
    print("COMPREHENSIVE GRAPH ALGORITHMS DEMONSTRATION")
    print("=" * 80)
    
    # Example 1: Social network analysis
    print("\n1. Social Network Analysis")
    print("-" * 35)
    
    social_graph = ComprehensiveGraph(directed=False, weighted=False, debug=True)
    
    # Add social connections
    connections = [
        ('Alice', 'Bob'), ('Alice', 'Charlie'), ('Alice', 'Diana'),
        ('Bob', 'Eve'), ('Charlie', 'Frank'), ('Diana', 'Grace'),
        ('Eve', 'Frank'), ('Frank', 'Grace')
    ]
    
    for u, v in connections:
        social_graph.add_edge(u, v)
    
    social_graph.print_graph()
    
    # BFS for degrees of separation
    print("\nFinding degrees of separation using BFS:")
    bfs_result = social_graph.breadth_first_search('Alice')
    
    # Example 2: Course prerequisites (topological sort)
    print("\n2. Course Prerequisites (Topological Sort)")
    print("-" * 50)
    
    course_graph = ComprehensiveGraph(directed=True, weighted=False, debug=True)
    
    # Add course prerequisites
    prerequisites = [
        ('CS101', 'CS102'), ('CS102', 'CS201'), ('CS201', 'CS301'),
        ('MATH101', 'CS201'), ('MATH101', 'MATH201'), ('CS301', 'CS401')
    ]
    
    for prereq, course in prerequisites:
        course_graph.add_edge(prereq, course)
    
    course_graph.print_graph()
    
    # Topological sort
    topo_result = course_graph.topological_sort()
    
    # Example 3: Transportation network (shortest paths)
    print("\n3. Transportation Network (Shortest Paths)")
    print("-" * 50)
    
    transport_graph = ComprehensiveGraph(directed=True, weighted=True, debug=True)
    
    # Add transportation routes with travel times
    routes = [
        ('NYC', 'Boston', 4), ('NYC', 'DC', 3), ('Boston', 'Chicago', 8),
        ('DC', 'Atlanta', 7), ('Atlanta', 'Miami', 9), ('Chicago', 'Denver', 12),
        ('Denver', 'LA', 15), ('LA', 'SanFran', 1)
    ]
    
    for u, v, time_cost in routes:
        transport_graph.add_edge(u, v, time_cost)
    
    transport_graph.print_graph()
    
    # Shortest path using Dijkstra
    print("\nFinding shortest path using Dijkstra:")
    dijkstra_result = transport_graph.dijkstra_shortest_path('NYC')
    
    # Find specific path
    path = transport_graph.find_shortest_path('NYC', 'LA', use_dijkstra=True)
    
    # Example 4: Network design (MST)
    print("\n4. Network Design (Minimum Spanning Tree)")
    print("-" * 50)
    
    network_graph = ComprehensiveGraph(directed=False, weighted=True, debug=True)
    
    # Add network connections with costs
    connections = [
        ('A', 'B', 4), ('A', 'C', 2), ('B', 'C', 1), ('B', 'D', 5),
        ('C', 'D', 8), ('C', 'E', 10), ('D', 'E', 2)
    ]
    
    for u, v, cost in connections:
        network_graph.add_edge(u, v, cost)
    
    network_graph.print_graph()
    
    # MST using Kruskal
    mst_result = network_graph.minimum_spanning_tree_kruskal()
    
    # Example 5: Cycle detection
    print("\n5. Cycle Detection Examples")
    print("-" * 35)
    
    # Directed graph with cycle
    cyclic_directed = ComprehensiveGraph(directed=True, weighted=False, debug=True)
    cyclic_directed.add_edge('A', 'B')
    cyclic_directed.add_edge('B', 'C')
    cyclic_directed.add_edge('C', 'A')  # Creates cycle
    
    print("Directed graph with cycle:")
    cyclic_directed.print_graph()
    has_cycle = cyclic_directed.detect_cycle()
    
    # Undirected graph with cycle
    cyclic_undirected = ComprehensiveGraph(directed=False, weighted=False, debug=True)
    cyclic_undirected.add_edge('A', 'B')
    cyclic_undirected.add_edge('B', 'C')
    cyclic_undirected.add_edge('C', 'A')  # Creates cycle
    
    print("\nUndirected graph with cycle:")
    cyclic_undirected.print_graph()
    has_cycle_undirected = cyclic_undirected.detect_cycle()
    
    # Example 6: Algorithm comparison and summary
    print("\n6. Algorithm Comparison and Summary")
    print("-" * 45)
    
    algorithms = {
        "BFS": {
            "time": "O(V + E)",
            "space": "O(V)",
            "use_case": "Shortest path (unweighted), level-order traversal"
        },
        "DFS": {
            "time": "O(V + E)",
            "space": "O(V)",
            "use_case": "Cycle detection, topological sort, connectivity"
        },
        "Dijkstra": {
            "time": "O((V + E) log V)",
            "space": "O(V)",
            "use_case": "Shortest path (non-negative weights)"
        },
        "Topological Sort": {
            "time": "O(V + E)",
            "space": "O(V)",
            "use_case": "DAG ordering, dependency resolution"
        },
        "Kruskal MST": {
            "time": "O(E log E)",
            "space": "O(V)",
            "use_case": "Minimum spanning tree, network design"
        }
    }
    
    print("Algorithm Complexity and Use Cases:")
    for algorithm, info in algorithms.items():
        print(f"\n{algorithm}:")
        print(f"  Time: {info['time']}")
        print(f"  Space: {info['space']}")
        print(f"  Use Case: {info['use_case']}")
    
    print("\n" + "=" * 80)
    print("DEMONSTRATION COMPLETED")
    print("=" * 80)


if __name__ == "__main__":
    demonstrate_comprehensive_algorithms()
