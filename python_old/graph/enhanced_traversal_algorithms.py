"""
Enhanced Graph Traversal Algorithms: BFS and DFS
Comprehensive implementation with extensive educational comments

This module demonstrates breadth-first search (BFS) and depth-first search (DFS)
with detailed explanations, step-by-step execution tracking, and real-world applications.
"""

from collections import deque, defaultdict
from typing import Dict, List, Set, Optional, Tuple, Any
from enum import Enum
import time


class VertexColor(Enum):
    """
    Three-color system for DFS algorithm.
    
    Educational Purpose:
    - WHITE: Unvisited vertex (initial state)
    - GRAY: Currently being processed (discovered but not finished)
    - BLACK: Completely processed (finished)
    
    This color system helps in:
    - Cycle detection in directed graphs
    - Understanding DFS execution order
    - Implementing topological sorting
    - Finding strongly connected components
    """
    WHITE = "WHITE"
    GRAY = "GRAY"
    BLACK = "BLACK"


class GraphTraversal:
    """
    Comprehensive graph traversal implementation with educational features.
    
    Educational Goals:
    1. Understand BFS and DFS algorithms deeply
    2. Learn when to use each traversal method
    3. See real-world applications of each algorithm
    4. Understand complexity analysis
    5. Learn debugging and visualization techniques
    """
    
    def __init__(self, graph: Dict[str, List[Tuple[str, float]]], directed: bool = False):
        """
        Initialize graph traversal with adjacency list representation.
        
        Args:
            graph: Dictionary mapping vertices to lists of (neighbor, weight) tuples
            directed: True if graph is directed, False if undirected
            
        Educational Note:
        - We use adjacency list for efficiency in traversal algorithms
        - Most real-world graphs are sparse, making adjacency list preferred
        - Weight information is preserved for algorithms that need it
        """
        self.graph = graph
        self.directed = directed
        self.vertices = set(graph.keys())
        
        # Add all vertices that appear as neighbors
        for neighbors in graph.values():
            for neighbor, _ in neighbors:
                self.vertices.add(neighbor)
    
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
            Dictionary containing:
            - traversal_order: Order in which vertices were visited
            - distances: Shortest distance from start to each vertex
            - parents: Parent vertex for path reconstruction
            - levels: Vertices at each distance level
            - target_found: Whether target was found (if specified)
            - execution_time: Time taken for the algorithm
            
        Time Complexity: O(V + E) where V is vertices, E is edges
        Space Complexity: O(V) for queue and visited tracking
        """
        print(f"Breadth-First Search starting from vertex: {start}")
        print("=" * 60)
        
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
        
        print(f"Level {current_level}: {levels[current_level]}")
        
        # BFS main loop
        while queue:
            current_vertex = queue.popleft()
            current_distance = distances[current_vertex]
            
            print(f"\nProcessing vertex: {current_vertex} (distance: {current_distance})")
            
            # Check if we found the target
            if target and current_vertex == target:
                print(f"🎯 Target {target} found at distance {current_distance}!")
                break
            
            # Explore neighbors
            neighbors_added = []
            if current_vertex in self.graph:
                for neighbor, weight in self.graph[current_vertex]:
                    if neighbor not in visited:
                        # Discover new vertex
                        visited.add(neighbor)
                        queue.append(neighbor)
                        distances[neighbor] = current_distance + 1
                        parents[neighbor] = current_vertex
                        traversal_order.append(neighbor)
                        neighbors_added.append(neighbor)
                        
                        print(f"  → Discovered {neighbor} at distance {current_distance + 1}")
            
            # Update levels for visualization
            if neighbors_added:
                next_level = current_distance + 1
                if next_level not in levels:
                    levels[next_level] = []
                levels[next_level].extend(neighbors_added)
                print(f"  Level {next_level}: {levels[next_level]}")
        
        execution_time = time.time() - start_time
        
        # Prepare results
        result = {
            'traversal_order': traversal_order,
            'distances': distances,
            'parents': parents,
            'levels': levels,
            'target_found': target in visited if target else None,
            'execution_time': execution_time,
            'vertices_visited': len(visited),
            'total_vertices': len(self.vertices)
        }
        
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
            Dictionary containing:
            - traversal_order: Order in which vertices were discovered
            - discovery_time: When each vertex was first discovered
            - finish_time: When each vertex was completely processed
            - parents: Parent vertex for path reconstruction
            - target_found: Whether target was found (if specified)
            - execution_time: Time taken for the algorithm
            - tree_edges: Edges that form the DFS tree
            - back_edges: Back edges (indicate cycles in directed graphs)
            
        Time Complexity: O(V + E) where V is vertices, E is edges
        Space Complexity: O(V) for recursion stack and tracking
        """
        print(f"Depth-First Search starting from vertex: {start}")
        print("=" * 60)
        
        start_time = time.time()
        
        # Initialize tracking variables
        color = {vertex: VertexColor.WHITE for vertex in self.vertices}
        discovery_time = {}
        finish_time = {}
        parents = {}
        traversal_order = []
        tree_edges = []
        back_edges = []
        time_counter = 0
        
        def dfs_visit(vertex: str, parent: Optional[str] = None) -> bool:
            """
            Recursive DFS visit function.
            
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
            
            print(f"  Discovering {vertex} at time {time_counter}")
            
            # Check if we found the target
            if target and vertex == target:
                print(f"🎯 Target {target} found!")
                return True
            
            # Explore neighbors
            if vertex in self.graph:
                for neighbor, weight in self.graph[vertex]:
                    if color[neighbor] == VertexColor.WHITE:
                        # Tree edge - exploring new vertex
                        tree_edges.append((vertex, neighbor))
                        print(f"    Tree edge: {vertex} → {neighbor}")
                        if dfs_visit(neighbor, vertex):
                            return True
                    elif color[neighbor] == VertexColor.GRAY:
                        # Back edge - cycle detected in directed graphs
                        back_edges.append((vertex, neighbor))
                        print(f"    Back edge: {vertex} → {neighbor} (cycle detected!)")
                    else:
                        # Forward or cross edge
                        print(f"    Forward/Cross edge: {vertex} → {neighbor}")
            
            # Mark vertex as finished
            time_counter += 1
            finish_time[vertex] = time_counter
            color[vertex] = VertexColor.BLACK
            
            print(f"  Finishing {vertex} at time {time_counter}")
            return False
        
        # Start DFS from specified vertex
        target_found = dfs_visit(start)
        
        # Visit any remaining unvisited vertices (for disconnected graphs)
        for vertex in self.vertices:
            if color[vertex] == VertexColor.WHITE:
                print(f"\nStarting DFS from disconnected vertex: {vertex}")
                if dfs_visit(vertex):
                    target_found = True
        
        execution_time = time.time() - start_time
        
        # Prepare results
        result = {
            'traversal_order': traversal_order,
            'discovery_time': discovery_time,
            'finish_time': finish_time,
            'parents': parents,
            'target_found': target_found,
            'execution_time': execution_time,
            'tree_edges': tree_edges,
            'back_edges': back_edges,
            'vertices_visited': len(traversal_order),
            'total_vertices': len(self.vertices)
        }
        
        print(f"\nDFS Summary:")
        print(f"  Vertices visited: {result['vertices_visited']}/{result['total_vertices']}")
        print(f"  Execution time: {execution_time:.6f} seconds")
        print(f"  Tree edges: {tree_edges}")
        if back_edges:
            print(f"  Back edges (cycles): {back_edges}")
        
        return result
    
    def find_shortest_path(self, start: str, end: str, use_bfs: bool = True) -> Optional[List[str]]:
        """
        Find shortest path between two vertices using BFS or DFS.
        
        Educational Note:
        - BFS finds shortest path in unweighted graphs
        - DFS finds any path (not necessarily shortest)
        - For weighted graphs, use Dijkstra's algorithm instead
        
        Args:
            start: Starting vertex
            end: Destination vertex
            use_bfs: True for BFS (shortest path), False for DFS (any path)
            
        Returns:
            List of vertices forming the path, or None if no path exists
            
        Time Complexity: O(V + E) for both BFS and DFS
        """
        if use_bfs:
            result = self.breadth_first_search(start, end)
            parents = result['parents']
            algorithm_name = "BFS"
        else:
            result = self.depth_first_search(start, end)
            parents = result['parents']
            algorithm_name = "DFS"
        
        if end not in parents:
            print(f"No path found from {start} to {end} using {algorithm_name}")
            return None
        
        # Reconstruct path
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = parents[current]
        
        path.reverse()
        
        print(f"{algorithm_name} Path from {start} to {end}: {' → '.join(path)}")
        if use_bfs:
            print(f"Path length: {len(path) - 1} edges")
        
        return path
    
    def detect_cycle_directed(self) -> bool:
        """
        Detect cycles in directed graphs using DFS with three-color system.
        
        Algorithm:
        - WHITE: Unvisited
        - GRAY: Currently being processed (in recursion stack)
        - BLACK: Completely processed
        
        Cycle exists if we encounter a GRAY vertex during DFS.
        
        Returns:
            True if cycle exists, False otherwise
            
        Time Complexity: O(V + E)
        """
        print("Cycle Detection in Directed Graph using DFS")
        print("=" * 50)
        
        color = {vertex: VertexColor.WHITE for vertex in self.vertices}
        
        def has_cycle_visit(vertex: str) -> bool:
            """
            Recursive function to detect cycles.
            
            Args:
                vertex: Current vertex being processed
                
            Returns:
                True if cycle detected, False otherwise
            """
            color[vertex] = VertexColor.GRAY
            print(f"  Processing {vertex} (GRAY)")
            
            # Check all neighbors
            if vertex in self.graph:
                for neighbor, _ in self.graph[vertex]:
                    if color[neighbor] == VertexColor.GRAY:
                        print(f"    Back edge to {neighbor} detected - CYCLE FOUND!")
                        return True
                    elif color[neighbor] == VertexColor.WHITE:
                        if has_cycle_visit(neighbor):
                            return True
            
            color[vertex] = VertexColor.BLACK
            print(f"  Finished {vertex} (BLACK)")
            return False
        
        # Check all vertices (for disconnected graphs)
        for vertex in self.vertices:
            if color[vertex] == VertexColor.WHITE:
                print(f"Starting cycle detection from {vertex}")
                if has_cycle_visit(vertex):
                    return True
        
        print("No cycles detected")
        return False
    
    def detect_cycle_undirected(self) -> bool:
        """
        Detect cycles in undirected graphs using DFS.
        
        Algorithm:
        - Use DFS with parent tracking
        - Cycle exists if we find an edge to a visited vertex that's not the parent
        
        Returns:
            True if cycle exists, False otherwise
            
        Time Complexity: O(V + E)
        """
        print("Cycle Detection in Undirected Graph using DFS")
        print("=" * 50)
        
        visited = set()
        
        def has_cycle_visit(vertex: str, parent: Optional[str] = None) -> bool:
            """
            Recursive function to detect cycles in undirected graph.
            
            Args:
                vertex: Current vertex being processed
                parent: Parent vertex in DFS tree
                
            Returns:
                True if cycle detected, False otherwise
            """
            visited.add(vertex)
            print(f"  Processing {vertex}")
            
            # Check all neighbors
            if vertex in self.graph:
                for neighbor, _ in self.graph[vertex]:
                    if neighbor not in visited:
                        if has_cycle_visit(neighbor, vertex):
                            return True
                    elif neighbor != parent:
                        print(f"    Back edge to {neighbor} detected - CYCLE FOUND!")
                        return True
            
            return False
        
        # Check all vertices (for disconnected graphs)
        for vertex in self.vertices:
            if vertex not in visited:
                print(f"Starting cycle detection from {vertex}")
                if has_cycle_visit(vertex):
                    return True
        
        print("No cycles detected")
        return False
    
    def find_connected_components(self) -> List[List[str]]:
        """
        Find all connected components in undirected graph using DFS.
        
        Educational Purpose:
        - Shows how to handle disconnected graphs
        - Demonstrates DFS for connectivity analysis
        - Useful for social network analysis (friend groups)
        
        Returns:
            List of connected components, each as a list of vertices
            
        Time Complexity: O(V + E)
        """
        print("Finding Connected Components using DFS")
        print("=" * 45)
        
        visited = set()
        components = []
        
        def dfs_component(vertex: str, component: List[str]) -> None:
            """
            DFS to find all vertices in current component.
            
            Args:
                vertex: Current vertex being processed
                component: List to store vertices in current component
            """
            visited.add(vertex)
            component.append(vertex)
            
            if vertex in self.graph:
                for neighbor, _ in self.graph[vertex]:
                    if neighbor not in visited:
                        dfs_component(neighbor, component)
        
        # Find components
        for vertex in self.vertices:
            if vertex not in visited:
                component = []
                dfs_component(vertex, component)
                components.append(component)
                print(f"Component {len(components)}: {component}")
        
        print(f"Found {len(components)} connected components")
        return components
    
    def visualize_traversal(self, result: Dict[str, Any], algorithm: str) -> None:
        """
        Visualize traversal results in a readable format.
        
        Args:
            result: Result dictionary from BFS or DFS
            algorithm: "BFS" or "DFS"
        """
        print(f"\n{algorithm} Visualization:")
        print("-" * 30)
        
        if algorithm == "BFS":
            print("Level-by-level traversal:")
            for level, vertices in result['levels'].items():
                print(f"  Level {level}: {vertices}")
        else:
            print("Discovery and finish times:")
            for vertex in result['traversal_order']:
                disc_time = result['discovery_time'].get(vertex, 'N/A')
                finish_time = result['finish_time'].get(vertex, 'N/A')
                print(f"  {vertex}: discovered at {disc_time}, finished at {finish_time}")


def demonstrate_traversal_algorithms():
    """
    Comprehensive demonstration of BFS and DFS algorithms.
    
    Educational Goals:
    1. Show practical applications of both algorithms
    2. Demonstrate when to use each algorithm
    3. Provide hands-on experience with graph traversal
    4. Show debugging and visualization techniques
    """
    
    print("=" * 80)
    print("COMPREHENSIVE GRAPH TRAVERSAL ALGORITHMS DEMONSTRATION")
    print("=" * 80)
    
    # Example 1: Social network traversal
    print("\n1. Social Network Example")
    print("-" * 30)
    
    social_network = {
        'Alice': [('Bob', 1), ('Charlie', 1), ('Diana', 1)],
        'Bob': [('Alice', 1), ('Eve', 1)],
        'Charlie': [('Alice', 1), ('Frank', 1)],
        'Diana': [('Alice', 1), ('Grace', 1)],
        'Eve': [('Bob', 1), ('Frank', 1)],
        'Frank': [('Charlie', 1), ('Eve', 1), ('Grace', 1)],
        'Grace': [('Diana', 1), ('Frank', 1)]
    }
    
    print("Social Network Graph:")
    print("    Alice")
    print("   /  |  \\")
    print(" Bob  |  Diana")
    print("  |   |    |")
    print(" Eve  |  Grace")
    print("  |   |    |")
    print(" Frank -----")
    
    traversal = GraphTraversal(social_network, directed=False)
    
    # BFS demonstration
    print("\nBFS: Finding degrees of separation")
    bfs_result = traversal.breadth_first_search('Alice')
    traversal.visualize_traversal(bfs_result, "BFS")
    
    # DFS demonstration
    print("\nDFS: Exploring friend connections")
    dfs_result = traversal.depth_first_search('Alice')
    traversal.visualize_traversal(dfs_result, "DFS")
    
    # Path finding
    print("\nPath Finding:")
    path = traversal.find_shortest_path('Alice', 'Grace', use_bfs=True)
    
    # Example 2: Web crawling simulation
    print("\n2. Web Crawling Simulation")
    print("-" * 35)
    
    web_pages = {
        'home': [('about', 1), ('products', 1), ('contact', 1)],
        'about': [('team', 1), ('history', 1)],
        'products': [('product1', 1), ('product2', 1)],
        'contact': [('support', 1)],
        'team': [('member1', 1)],
        'history': [],
        'product1': [],
        'product2': [],
        'support': [],
        'member1': []
    }
    
    web_crawler = GraphTraversal(web_pages, directed=True)
    
    print("Web Crawling with BFS (level-by-level discovery):")
    web_bfs = web_crawler.breadth_first_search('home')
    
    print("\nWeb Crawling with DFS (following links deeply):")
    web_dfs = web_crawler.depth_first_search('home')
    
    # Example 3: Cycle detection
    print("\n3. Cycle Detection Examples")
    print("-" * 35)
    
    # Directed graph with cycle
    cyclic_directed = {
        'A': [('B', 1)],
        'B': [('C', 1)],
        'C': [('A', 1)],  # Creates cycle A->B->C->A
        'D': [('E', 1)],
        'E': []
    }
    
    print("Directed graph with cycle:")
    print("A → B → C → A (cycle)")
    print("D → E")
    
    cyclic_traversal = GraphTraversal(cyclic_directed, directed=True)
    has_cycle = cyclic_traversal.detect_cycle_directed()
    
    # Undirected graph with cycle
    cyclic_undirected = {
        'A': [('B', 1), ('C', 1)],
        'B': [('A', 1), ('C', 1)],  # Creates cycle A-B-C-A
        'C': [('A', 1), ('B', 1)],
        'D': [('E', 1)],
        'E': [('D', 1)]
    }
    
    print("\nUndirected graph with cycle:")
    print("A - B - C - A (cycle)")
    print("D - E")
    
    undirected_traversal = GraphTraversal(cyclic_undirected, directed=False)
    has_cycle_undirected = undirected_traversal.detect_cycle_undirected()
    
    # Example 4: Connected components
    print("\n4. Connected Components Analysis")
    print("-" * 40)
    
    disconnected_graph = {
        'A': [('B', 1), ('C', 1)],
        'B': [('A', 1)],
        'C': [('A', 1)],
        'D': [('E', 1)],
        'E': [('D', 1)],
        'F': []  # Isolated vertex
    }
    
    print("Disconnected graph:")
    print("Component 1: A - B - C")
    print("Component 2: D - E")
    print("Component 3: F (isolated)")
    
    disconnected_traversal = GraphTraversal(disconnected_graph, directed=False)
    components = disconnected_traversal.find_connected_components()
    
    # Example 5: Algorithm comparison
    print("\n5. BFS vs DFS Comparison")
    print("-" * 35)
    
    print("When to use BFS:")
    print("  - Shortest path in unweighted graphs")
    print("  - Level-order traversal")
    print("  - Web crawling (breadth-first)")
    print("  - Social network analysis (degrees of separation)")
    print("  - Game AI (minimum moves)")
    
    print("\nWhen to use DFS:")
    print("  - Cycle detection")
    print("  - Topological sorting")
    print("  - Finding strongly connected components")
    print("  - Maze solving")
    print("  - Game tree exploration")
    print("  - Dependency resolution")
    
    print("\nComplexity Comparison:")
    print("  BFS: Time O(V+E), Space O(V) for queue")
    print("  DFS: Time O(V+E), Space O(V) for recursion stack")
    
    # Example 6: Real-world applications summary
    print("\n6. Real-World Applications Summary")
    print("-" * 40)
    
    applications = {
        "BFS": [
            "GPS navigation (shortest routes)",
            "Social media (friend suggestions)",
            "Web crawling (systematic page discovery)",
            "Network broadcasting (information propagation)",
            "Game AI (finding optimal moves)"
        ],
        "DFS": [
            "Compiler dependency resolution",
            "Maze solving and pathfinding",
            "Cycle detection in systems",
            "Topological sorting of tasks",
            "Finding strongly connected components"
        ]
    }
    
    for algorithm, apps in applications.items():
        print(f"\n{algorithm} Applications:")
        for app in apps:
            print(f"  • {app}")


if __name__ == "__main__":
    demonstrate_traversal_algorithms()
