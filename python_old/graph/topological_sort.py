"""
Topological Sorting Algorithms: Kahn's and DFS-based
Demonstrates topological sorting with cycle detection
"""

from collections import deque
from typing import List, Dict, Set, Optional, Tuple
from graph_class import Graph


class TopologicalSort:
    """Class containing topological sorting algorithm implementations."""
    
    def __init__(self, graph: Graph):
        if not graph.directed:
            raise ValueError("Topological sort only works on directed graphs")
        self.graph = graph
    
    def kahn_algorithm(self) -> Tuple[List[str], bool]:
        """
        Kahn's algorithm for topological sorting.
        
        Returns:
            Tuple of (topological_order, has_cycle)
        """
        print("Kahn's Algorithm for Topological Sorting")
        print("=" * 45)
        
        # Calculate in-degrees
        in_degree = {vertex: 0 for vertex in self.graph.vertices}
        
        for u, v, _ in self.graph.edges:
            in_degree[v] += 1
        
        print(f"In-degrees: {in_degree}")
        
        # Initialize queue with vertices of in-degree 0
        queue = deque([v for v, degree in in_degree.items() if degree == 0])
        print(f"Initial queue (in-degree 0): {list(queue)}")
        
        topological_order = []
        step = 1
        
        while queue:
            current_vertex = queue.popleft()
            topological_order.append(current_vertex)
            
            print(f"\nStep {step}: Processing vertex {current_vertex}")
            print(f"  Current order: {topological_order}")
            
            # Process all outgoing edges
            for neighbor, _ in self.graph.get_neighbors(current_vertex):
                in_degree[neighbor] -= 1
                print(f"  Decreased in-degree of {neighbor}: {in_degree[neighbor] + 1} -> {in_degree[neighbor]}")
                
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
                    print(f"  Added {neighbor} to queue")
            
            step += 1
        
        # Check for cycle
        has_cycle = len(topological_order) != len(self.graph.vertices)
        
        if has_cycle:
            print(f"\nCycle detected! Only {len(topological_order)} vertices processed out of {len(self.graph.vertices)}")
        else:
            print(f"\nTopological sort completed successfully!")
        
        return topological_order, has_cycle
    
    def dfs_algorithm(self) -> Tuple[List[str], bool]:
        """
        DFS-based topological sorting.
        
        Returns:
            Tuple of (topological_order, has_cycle)
        """
        print("\nDFS-based Topological Sorting")
        print("=" * 35)
        
        # Three colors: WHITE (unvisited), GRAY (visiting), BLACK (visited)
        color = {vertex: 'WHITE' for vertex in self.graph.vertices}
        topological_order = []
        has_cycle = False
        
        def dfs_visit(vertex: str) -> bool:
            nonlocal has_cycle
            color[vertex] = 'GRAY'
            print(f"  Visiting {vertex} (GRAY)")
            
            for neighbor, _ in self.graph.get_neighbors(vertex):
                if color[neighbor] == 'GRAY':
                    print(f"    Back edge to {neighbor} detected - cycle found!")
                    has_cycle = True
                    return True
                elif color[neighbor] == 'WHITE':
                    if dfs_visit(neighbor):
                        return True
            
            color[vertex] = 'BLACK'
            topological_order.insert(0, vertex)  # Add to front
            print(f"  Finished {vertex} (BLACK) - added to front of order")
            return False
        
        # Visit all vertices
        for vertex in self.graph.vertices:
            if color[vertex] == 'WHITE':
                print(f"\nStarting DFS from {vertex}")
                if dfs_visit(vertex):
                    break
        
        if has_cycle:
            print(f"\nCycle detected during DFS!")
        else:
            print(f"\nDFS topological sort completed!")
        
        return topological_order, has_cycle
    
    def compare_algorithms(self) -> None:
        """Compare Kahn's and DFS algorithms."""
        print("\n" + "=" * 50)
        print("COMPARING KAHN vs DFS ALGORITHMS")
        print("=" * 50)
        
        # Run both algorithms
        kahn_order, kahn_cycle = self.kahn_algorithm()
        dfs_order, dfs_cycle = self.dfs_algorithm()
        
        print(f"\nComparison Results:")
        print(f"  Kahn's order: {kahn_order}")
        print(f"  DFS order: {dfs_order}")
        print(f"  Kahn detected cycle: {kahn_cycle}")
        print(f"  DFS detected cycle: {dfs_cycle}")
        print(f"  Cycle detection consistent: {kahn_cycle == dfs_cycle}")
        
        if not kahn_cycle and not dfs_cycle:
            print(f"  Orders are valid topological sorts: {kahn_order == dfs_order}")
    
    def find_all_topological_orders(self) -> List[List[str]]:
        """
        Find all possible topological orders using backtracking.
        Only works for DAGs (no cycles).
        
        Returns:
            List of all possible topological orders
        """
        print("\nFinding All Topological Orders")
        print("=" * 35)
        
        # First check if graph is a DAG
        _, has_cycle = self.kahn_algorithm()
        if has_cycle:
            print("Graph contains cycles - no valid topological orders exist")
            return []
        
        all_orders = []
        in_degree = {vertex: 0 for vertex in self.graph.vertices}
        
        # Calculate in-degrees
        for u, v, _ in self.graph.edges:
            in_degree[v] += 1
        
        def backtrack(current_order: List[str], remaining_in_degree: Dict[str, int]):
            if len(current_order) == len(self.graph.vertices):
                all_orders.append(current_order.copy())
                return
            
            # Find vertices with in-degree 0
            candidates = [v for v, degree in remaining_in_degree.items() if degree == 0 and v not in current_order]
            
            for vertex in candidates:
                # Choose vertex
                current_order.append(vertex)
                new_in_degree = remaining_in_degree.copy()
                
                # Update in-degrees
                for neighbor, _ in self.graph.get_neighbors(vertex):
                    new_in_degree[neighbor] -= 1
                
                # Recurse
                backtrack(current_order, new_in_degree)
                
                # Backtrack
                current_order.pop()
        
        backtrack([], in_degree)
        
        print(f"Found {len(all_orders)} valid topological orders:")
        for i, order in enumerate(all_orders, 1):
            print(f"  {i}: {order}")
        
        return all_orders


def demonstrate_topological_sorting():
    """Demonstrate topological sorting algorithms with examples."""
    
    print("=" * 70)
    print("TOPOLOGICAL SORTING ALGORITHMS DEMONSTRATION")
    print("=" * 70)
    
    # Create sample graphs
    print("\n1. Creating Sample Graphs")
    print("-" * 30)
    
    # DAG for topological sorting
    dag_graph = Graph(directed=True)
    dag_graph.add_edge('A', 'B')
    dag_graph.add_edge('A', 'C')
    dag_graph.add_edge('B', 'D')
    dag_graph.add_edge('C', 'D')
    dag_graph.add_edge('C', 'E')
    dag_graph.add_edge('D', 'F')
    dag_graph.add_edge('E', 'F')
    
    print("DAG (Directed Acyclic Graph):")
    dag_graph.print_adjacency_list()
    
    # Graph with cycle
    cyclic_graph = Graph(directed=True)
    cyclic_graph.add_edge('A', 'B')
    cyclic_graph.add_edge('B', 'C')
    cyclic_graph.add_edge('C', 'A')  # Creates a cycle
    cyclic_graph.add_edge('C', 'D')
    cyclic_graph.add_edge('D', 'E')
    
    print("\nCyclic Graph:")
    cyclic_graph.print_adjacency_list()
    
    # Demonstrate Kahn's algorithm on DAG
    print("\n2. Kahn's Algorithm on DAG")
    print("-" * 35)
    ts_dag = TopologicalSort(dag_graph)
    kahn_order, kahn_cycle = ts_dag.kahn_algorithm()
    
    if not kahn_cycle:
        print(f"\nValid topological order: {kahn_order}")
    
    # Demonstrate DFS algorithm on DAG
    print("\n3. DFS Algorithm on DAG")
    print("-" * 30)
    dfs_order, dfs_cycle = ts_dag.dfs_algorithm()
    
    if not dfs_cycle:
        print(f"\nValid topological order: {dfs_order}")
    
    # Compare algorithms
    print("\n4. Algorithm Comparison on DAG")
    print("-" * 40)
    ts_dag.compare_algorithms()
    
    # Test with cyclic graph
    print("\n5. Testing with Cyclic Graph")
    print("-" * 35)
    ts_cyclic = TopologicalSort(cyclic_graph)
    cyclic_kahn_order, cyclic_kahn_cycle = ts_cyclic.kahn_algorithm()
    cyclic_dfs_order, cyclic_dfs_cycle = ts_cyclic.dfs_algorithm()
    
    print(f"Kahn's result: {cyclic_kahn_order}, cycle: {cyclic_kahn_cycle}")
    print(f"DFS result: {cyclic_dfs_order}, cycle: {cyclic_dfs_cycle}")
    
    # Find all topological orders
    print("\n6. Finding All Topological Orders")
    print("-" * 40)
    all_orders = ts_dag.find_all_topological_orders()
    
    # Real-world example: Course prerequisites
    print("\n7. Real-World Example: Course Prerequisites")
    print("-" * 50)
    
    course_graph = Graph(directed=True)
    course_graph.add_edge('CS101', 'CS102')  # CS102 requires CS101
    course_graph.add_edge('CS102', 'CS201')  # CS201 requires CS102
    course_graph.add_edge('CS201', 'CS301')  # CS301 requires CS201
    course_graph.add_edge('CS301', 'CS401')  # CS401 requires CS301
    course_graph.add_edge('MATH101', 'CS201')  # CS201 also requires MATH101
    course_graph.add_edge('MATH101', 'MATH201')  # MATH201 requires MATH101
    
    print("Course Prerequisites Graph:")
    course_graph.print_adjacency_list()
    
    ts_courses = TopologicalSort(course_graph)
    course_order, course_cycle = ts_courses.kahn_algorithm()
    
    if not course_cycle:
        print(f"\nValid course sequence: {' -> '.join(course_order)}")
        print("\nThis means students can take courses in this order without conflicts.")
    
    # Visual representation
    print("\n8. Visual Graph Representation")
    print("-" * 35)
    print("DAG Structure:")
    print("    A")
    print("   / \\")
    print("  B   C")
    print("  |   |\\")
    print("  D   E |")
    print("  \\   /")
    print("    F")
    
    print("\nTopological Order (one possible): A -> B -> C -> D -> E -> F")
    
    # Algorithm complexity analysis
    print("\n9. Algorithm Complexity Analysis")
    print("-" * 40)
    print("Kahn's Algorithm:")
    print("  Time: O(V + E)")
    print("  Space: O(V)")
    print("  Advantages: Simple, detects cycles")
    
    print("\nDFS Algorithm:")
    print("  Time: O(V + E)")
    print("  Space: O(V) for recursion stack")
    print("  Advantages: Natural for many problems, can find all orders")


if __name__ == "__main__":
    demonstrate_topological_sorting()
