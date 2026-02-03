"""
Graph Traversal Algorithms: BFS and DFS
Demonstrates breadth-first and depth-first search with visualization
"""

from collections import deque
from typing import List, Dict, Set, Tuple, Optional
from graph_class import Graph


class GraphTraversal:
    """Class containing BFS and DFS implementations with visualization."""
    
    def __init__(self, graph: Graph):
        self.graph = graph
    
    def bfs(self, start: str, target: Optional[str] = None) -> Dict[str, any]:
        """
        Breadth-First Search implementation.
        
        Args:
            start: Starting vertex
            target: Optional target vertex to search for
            
        Returns:
            Dictionary containing traversal order, distances, and parents
        """
        if start not in self.graph.vertices:
            raise ValueError(f"Vertex {start} not in graph")
        
        # Initialize
        visited = set()
        queue = deque([start])
        visited.add(start)
        traversal_order = [start]
        distances = {start: 0}
        parents = {start: None}
        levels = {0: [start]}
        current_level = 0
        
        print(f"BFS starting from vertex: {start}")
        print(f"Level {current_level}: {levels[current_level]}")
        
        while queue:
            current_vertex = queue.popleft()
            current_distance = distances[current_vertex]
            
            # Check if we found the target
            if target and current_vertex == target:
                print(f"Target {target} found at distance {current_distance}")
                break
            
            # Explore neighbors
            neighbors_added = []
            for neighbor, weight in self.graph.get_neighbors(current_vertex):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
                    distances[neighbor] = current_distance + 1
                    parents[neighbor] = current_vertex
                    traversal_order.append(neighbor)
                    neighbors_added.append(neighbor)
            
            # Update levels for visualization
            if neighbors_added:
                next_level = current_distance + 1
                if next_level not in levels:
                    levels[next_level] = []
                levels[next_level].extend(neighbors_added)
                print(f"Level {next_level}: {levels[next_level]}")
        
        return {
            'traversal_order': traversal_order,
            'distances': distances,
            'parents': parents,
            'levels': levels,
            'target_found': target in visited if target else None
        }
    
    def dfs(self, start: str, target: Optional[str] = None) -> Dict[str, any]:
        """
        Depth-First Search implementation.
        
        Args:
            start: Starting vertex
            target: Optional target vertex to search for
            
        Returns:
            Dictionary containing traversal order, discovery/finish times, and parents
        """
        if start not in self.graph.vertices:
            raise ValueError(f"Vertex {start} not in graph")
        
        # Initialize
        visited = set()
        traversal_order = []
        discovery_time = {}
        finish_time = {}
        parents = {}
        time = 0
        
        print(f"DFS starting from vertex: {start}")
        
        def dfs_visit(vertex: str, parent: Optional[str] = None):
            nonlocal time
            time += 1
            discovery_time[vertex] = time
            parents[vertex] = parent
            visited.add(vertex)
            traversal_order.append(vertex)
            
            print(f"Discovering {vertex} at time {time}")
            
            # Check if we found the target
            if target and vertex == target:
                print(f"Target {target} found!")
                return True
            
            # Explore neighbors
            for neighbor, weight in self.graph.get_neighbors(vertex):
                if neighbor not in visited:
                    if dfs_visit(neighbor, vertex):
                        return True
            
            time += 1
            finish_time[vertex] = time
            print(f"Finishing {vertex} at time {time}")
            return False
        
        # Start DFS
        target_found = dfs_visit(start)
        
        return {
            'traversal_order': traversal_order,
            'discovery_time': discovery_time,
            'finish_time': finish_time,
            'parents': parents,
            'target_found': target_found
        }
    
    def find_path(self, start: str, end: str, use_bfs: bool = True) -> Optional[List[str]]:
        """
        Find a path between two vertices.
        
        Args:
            start: Starting vertex
            end: Destination vertex
            use_bfs: If True, use BFS; otherwise use DFS
            
        Returns:
            List of vertices forming the path, or None if no path exists
        """
        if use_bfs:
            result = self.bfs(start, end)
            parents = result['parents']
        else:
            result = self.dfs(start, end)
            parents = result['parents']
        
        if end not in parents:
            return None
        
        # Reconstruct path
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = parents[current]
        
        return path[::-1]  # Reverse to get start -> end
    
    def detect_cycle(self) -> bool:
        """
        Detect if the graph contains a cycle.
        Uses DFS with three-color approach.
        
        Returns:
            True if cycle exists, False otherwise
        """
        # Three colors: WHITE (unvisited), GRAY (visiting), BLACK (visited)
        color = {vertex: 'WHITE' for vertex in self.graph.vertices}
        
        def has_cycle_visit(vertex: str, parent: Optional[str] = None) -> bool:
            color[vertex] = 'GRAY'
            
            for neighbor, _ in self.graph.get_neighbors(vertex):
                if neighbor == parent:  # Skip parent in undirected graph
                    continue
                
                if color[neighbor] == 'GRAY':
                    return True  # Back edge found - cycle detected
                elif color[neighbor] == 'WHITE':
                    if has_cycle_visit(neighbor, vertex):
                        return True
            
            color[vertex] = 'BLACK'
            return False
        
        # Check all components
        for vertex in self.graph.vertices:
            if color[vertex] == 'WHITE':
                if has_cycle_visit(vertex):
                    return True
        
        return False
    
    def find_connected_components(self) -> List[List[str]]:
        """
        Find all connected components in an undirected graph.
        
        Returns:
            List of connected components, each as a list of vertices
        """
        if self.graph.directed:
            raise ValueError("Connected components only defined for undirected graphs")
        
        visited = set()
        components = []
        
        def dfs_component(vertex: str, component: List[str]):
            visited.add(vertex)
            component.append(vertex)
            
            for neighbor, _ in self.graph.get_neighbors(vertex):
                if neighbor not in visited:
                    dfs_component(neighbor, component)
        
        for vertex in self.graph.vertices:
            if vertex not in visited:
                component = []
                dfs_component(vertex, component)
                components.append(component)
        
        return components


def demonstrate_traversal_algorithms():
    """Demonstrate BFS and DFS with various examples."""
    
    print("=" * 60)
    print("GRAPH TRAVERSAL ALGORITHMS DEMONSTRATION")
    print("=" * 60)
    
    # Create sample graphs
    print("\n1. Creating Sample Graphs")
    print("-" * 30)
    
    # Undirected graph for BFS/DFS
    undirected_graph = Graph(directed=False)
    undirected_graph.add_edge('A', 'B')
    undirected_graph.add_edge('A', 'C')
    undirected_graph.add_edge('B', 'D')
    undirected_graph.add_edge('C', 'D')
    undirected_graph.add_edge('C', 'E')
    undirected_graph.add_edge('D', 'F')
    undirected_graph.add_edge('E', 'F')
    
    print("Undirected Graph:")
    undirected_graph.print_adjacency_list()
    
    # Directed graph for cycle detection
    directed_graph = Graph(directed=True)
    directed_graph.add_edge('A', 'B')
    directed_graph.add_edge('B', 'C')
    directed_graph.add_edge('C', 'A')  # Creates a cycle
    directed_graph.add_edge('C', 'D')
    directed_graph.add_edge('D', 'E')
    
    print("\nDirected Graph:")
    directed_graph.print_adjacency_list()
    
    # Demonstrate BFS
    print("\n2. Breadth-First Search (BFS)")
    print("-" * 40)
    traversal = GraphTraversal(undirected_graph)
    bfs_result = traversal.bfs('A')
    
    print(f"\nBFS Traversal Order: {bfs_result['traversal_order']}")
    print(f"Distances from A: {bfs_result['distances']}")
    print(f"Parent relationships: {bfs_result['parents']}")
    
    # Demonstrate DFS
    print("\n3. Depth-First Search (DFS)")
    print("-" * 40)
    dfs_result = traversal.dfs('A')
    
    print(f"\nDFS Traversal Order: {dfs_result['traversal_order']}")
    print(f"Discovery times: {dfs_result['discovery_time']}")
    print(f"Finish times: {dfs_result['finish_time']}")
    print(f"Parent relationships: {dfs_result['parents']}")
    
    # Find paths
    print("\n4. Finding Paths")
    print("-" * 20)
    path_bfs = traversal.find_path('A', 'F', use_bfs=True)
    path_dfs = traversal.find_path('A', 'F', use_bfs=False)
    
    print(f"Path from A to F (BFS): {path_bfs}")
    print(f"Path from A to F (DFS): {path_dfs}")
    
    # Cycle detection
    print("\n5. Cycle Detection")
    print("-" * 20)
    undirected_traversal = GraphTraversal(undirected_graph)
    directed_traversal = GraphTraversal(directed_graph)
    
    print(f"Undirected graph has cycle: {undirected_traversal.detect_cycle()}")
    print(f"Directed graph has cycle: {directed_traversal.detect_cycle()}")
    
    # Connected components
    print("\n6. Connected Components")
    print("-" * 30)
    
    # Create a graph with multiple components
    multi_component_graph = Graph(directed=False)
    multi_component_graph.add_edge('A', 'B')
    multi_component_graph.add_edge('B', 'C')
    multi_component_graph.add_edge('D', 'E')
    multi_component_graph.add_vertex('F')  # Isolated vertex
    
    print("Multi-component graph:")
    multi_component_graph.print_adjacency_list()
    
    multi_traversal = GraphTraversal(multi_component_graph)
    components = multi_traversal.find_connected_components()
    
    print(f"Connected components: {components}")
    
    # Visual representation
    print("\n7. Visual Graph Representation")
    print("-" * 35)
    print("Undirected Graph Structure:")
    print("    A --- B")
    print("    |     |")
    print("    C --- D")
    print("    |     |")
    print("    E --- F")
    
    print("\nBFS Levels:")
    for level, vertices in bfs_result['levels'].items():
        print(f"  Level {level}: {vertices}")


if __name__ == "__main__":
    demonstrate_traversal_algorithms()
