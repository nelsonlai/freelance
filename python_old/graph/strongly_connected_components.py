"""
Strongly Connected Components Algorithms: Kosaraju and Tarjan
Demonstrates SCC algorithms for directed graphs
"""

from collections import defaultdict
from typing import List, Dict, Set, Tuple
from graph_class import Graph


class StronglyConnectedComponents:
    """Class containing SCC algorithm implementations."""
    
    def __init__(self, graph: Graph):
        if not graph.directed:
            raise ValueError("SCC algorithms only work on directed graphs")
        self.graph = graph
    
    def kosaraju_algorithm(self) -> List[List[str]]:
        """
        Kosaraju's algorithm for finding strongly connected components.
        
        Returns:
            List of SCCs, each as a list of vertices
        """
        print("Kosaraju's Algorithm for Strongly Connected Components")
        print("=" * 60)
        
        # Step 1: First DFS pass to get finish times
        print("Step 1: First DFS pass to get finish times")
        visited = set()
        finish_order = []
        
        def dfs_first_pass(vertex: str):
            visited.add(vertex)
            print(f"  Visiting {vertex}")
            
            for neighbor, _ in self.graph.get_neighbors(vertex):
                if neighbor not in visited:
                    dfs_first_pass(neighbor)
            
            finish_order.append(vertex)
            print(f"  Finished {vertex} (added to finish order)")
        
        for vertex in self.graph.vertices:
            if vertex not in visited:
                print(f"Starting DFS from {vertex}")
                dfs_first_pass(vertex)
        
        print(f"Finish order: {finish_order}")
        
        # Step 2: Reverse the graph
        print("\nStep 2: Reversing the graph")
        reversed_graph = self._reverse_graph()
        print("Reversed graph adjacency list:")
        for vertex in sorted(reversed_graph.keys()):
            neighbors = reversed_graph[vertex]
            neighbor_str = ", ".join(neighbors)
            print(f"  {vertex}: [{neighbor_str}]")
        
        # Step 3: Second DFS pass on reversed graph
        print("\nStep 3: Second DFS pass on reversed graph")
        visited = set()
        sccs = []
        
        def dfs_second_pass(vertex: str, current_scc: List[str]):
            visited.add(vertex)
            current_scc.append(vertex)
            print(f"  Visiting {vertex} (added to current SCC)")
            
            for neighbor in reversed_graph.get(vertex, []):
                if neighbor not in visited:
                    dfs_second_pass(neighbor, current_scc)
        
        # Process vertices in reverse finish order
        for vertex in reversed(finish_order):
            if vertex not in visited:
                current_scc = []
                print(f"Starting DFS from {vertex} in reversed graph")
                dfs_second_pass(vertex, current_scc)
                sccs.append(current_scc)
                print(f"  Completed SCC: {current_scc}")
        
        print(f"\nFinal SCCs: {sccs}")
        return sccs
    
    def tarjan_algorithm(self) -> List[List[str]]:
        """
        Tarjan's algorithm for finding strongly connected components.
        
        Returns:
            List of SCCs, each as a list of vertices
        """
        print("\nTarjan's Algorithm for Strongly Connected Components")
        print("=" * 55)
        
        # Initialize
        index = {}
        low_link = {}
        on_stack = set()
        stack = []
        sccs = []
        current_index = 0
        
        def strongconnect(vertex: str):
            nonlocal current_index
            index[vertex] = current_index
            low_link[vertex] = current_index
            current_index += 1
            stack.append(vertex)
            on_stack.add(vertex)
            
            print(f"  Processing {vertex}: index={index[vertex]}, low_link={low_link[vertex]}")
            
            for neighbor, _ in self.graph.get_neighbors(vertex):
                if neighbor not in index:
                    print(f"    {neighbor} not visited, recursing")
                    strongconnect(neighbor)
                    low_link[vertex] = min(low_link[vertex], low_link[neighbor])
                    print(f"    Updated low_link[{vertex}] = {low_link[vertex]}")
                elif neighbor in on_stack:
                    low_link[vertex] = min(low_link[vertex], index[neighbor])
                    print(f"    {neighbor} on stack, updated low_link[{vertex}] = {low_link[vertex]}")
            
            # If vertex is a root node, pop the stack and create an SCC
            if low_link[vertex] == index[vertex]:
                scc = []
                while True:
                    w = stack.pop()
                    on_stack.remove(w)
                    scc.append(w)
                    print(f"    Added {w} to SCC")
                    if w == vertex:
                        break
                
                sccs.append(scc)
                print(f"  Completed SCC: {scc}")
        
        # Process all vertices
        for vertex in self.graph.vertices:
            if vertex not in index:
                print(f"Starting Tarjan from {vertex}")
                strongconnect(vertex)
        
        print(f"\nFinal SCCs: {sccs}")
        return sccs
    
    def _reverse_graph(self) -> Dict[str, List[str]]:
        """Create a reversed version of the graph."""
        reversed_graph = defaultdict(list)
        
        for u, v, _ in self.graph.edges:
            reversed_graph[v].append(u)
        
        return dict(reversed_graph)
    
    def compare_algorithms(self) -> None:
        """Compare Kosaraju and Tarjan algorithms."""
        print("\n" + "=" * 50)
        print("COMPARING KOSARAJU vs TARJAN ALGORITHMS")
        print("=" * 50)
        
        # Run both algorithms
        kosaraju_sccs = self.kosaraju_algorithm()
        tarjan_sccs = self.tarjan_algorithm()
        
        print(f"\nComparison Results:")
        print(f"  Kosaraju SCCs: {kosaraju_sccs}")
        print(f"  Tarjan SCCs: {tarjan_sccs}")
        
        # Check if results are equivalent (order may differ)
        kosaraju_sets = [set(scc) for scc in kosaraju_sccs]
        tarjan_sets = [set(scc) for scc in tarjan_sccs]
        
        kosaraju_sets.sort(key=lambda x: min(x))  # Sort by minimum vertex
        tarjan_sets.sort(key=lambda x: min(x))
        
        print(f"  Results equivalent: {kosaraju_sets == tarjan_sets}")
    
    def analyze_scc_properties(self, sccs: List[List[str]]) -> None:
        """Analyze properties of the SCCs."""
        print(f"\nSCC Analysis:")
        print(f"  Number of SCCs: {len(sccs)}")
        print(f"  Total vertices: {sum(len(scc) for scc in sccs)}")
        
        for i, scc in enumerate(sccs):
            print(f"  SCC {i+1}: {scc} (size: {len(scc)})")
        
        # Check for single-vertex SCCs (sinks)
        single_vertex_sccs = [scc for scc in sccs if len(scc) == 1]
        if single_vertex_sccs:
            print(f"  Single-vertex SCCs (sinks): {single_vertex_sccs}")
        
        # Check for largest SCC
        largest_scc = max(sccs, key=len)
        print(f"  Largest SCC: {largest_scc} (size: {len(largest_scc)})")
    
    def create_condensation_graph(self, sccs: List[List[str]]) -> Graph:
        """
        Create the condensation graph where each SCC becomes a single vertex.
        
        Args:
            sccs: List of strongly connected components
            
        Returns:
            Condensation graph
        """
        print(f"\nCreating Condensation Graph")
        print("=" * 30)
        
        # Create mapping from vertex to SCC
        vertex_to_scc = {}
        for i, scc in enumerate(sccs):
            for vertex in scc:
                vertex_to_scc[vertex] = i
        
        # Create condensation graph
        condensation = Graph(directed=True)
        
        # Add vertices for each SCC
        for i, scc in enumerate(sccs):
            condensation.add_vertex(f"SCC_{i}")
        
        # Add edges between SCCs
        scc_edges = set()
        for u, v, weight in self.graph.edges:
            scc_u = vertex_to_scc[u]
            scc_v = vertex_to_scc[v]
            
            if scc_u != scc_v:  # Don't add self-loops
                scc_edges.add((scc_u, scc_v))
        
        for scc_u, scc_v in scc_edges:
            condensation.add_edge(f"SCC_{scc_u}", f"SCC_{scc_v}")
        
        print("Condensation graph:")
        condensation.print_adjacency_list()
        
        return condensation


def demonstrate_scc_algorithms():
    """Demonstrate SCC algorithms with examples."""
    
    print("=" * 70)
    print("STRONGLY CONNECTED COMPONENTS ALGORITHMS DEMONSTRATION")
    print("=" * 70)
    
    # Create sample graphs
    print("\n1. Creating Sample Graphs")
    print("-" * 30)
    
    # Graph with multiple SCCs
    scc_graph = Graph(directed=True)
    scc_graph.add_edge('A', 'B')
    scc_graph.add_edge('B', 'C')
    scc_graph.add_edge('C', 'A')  # SCC 1: A-B-C
    scc_graph.add_edge('C', 'D')
    scc_graph.add_edge('D', 'E')
    scc_graph.add_edge('E', 'D')  # SCC 2: D-E
    scc_graph.add_edge('E', 'F')
    scc_graph.add_vertex('G')  # SCC 3: G (isolated)
    
    print("Graph with multiple SCCs:")
    scc_graph.print_adjacency_list()
    
    # Simple cycle graph
    cycle_graph = Graph(directed=True)
    cycle_graph.add_edge('A', 'B')
    cycle_graph.add_edge('B', 'C')
    cycle_graph.add_edge('C', 'A')
    
    print("\nSimple cycle graph:")
    cycle_graph.print_adjacency_list()
    
    # Demonstrate Kosaraju's algorithm
    print("\n2. Kosaraju's Algorithm")
    print("-" * 30)
    scc_analyzer = StronglyConnectedComponents(scc_graph)
    kosaraju_sccs = scc_analyzer.kosaraju_algorithm()
    
    scc_analyzer.analyze_scc_properties(kosaraju_sccs)
    
    # Demonstrate Tarjan's algorithm
    print("\n3. Tarjan's Algorithm")
    print("-" * 25)
    tarjan_sccs = scc_analyzer.tarjan_algorithm()
    
    scc_analyzer.analyze_scc_properties(tarjan_sccs)
    
    # Compare algorithms
    print("\n4. Algorithm Comparison")
    print("-" * 30)
    scc_analyzer.compare_algorithms()
    
    # Create condensation graph
    print("\n5. Condensation Graph")
    print("-" * 25)
    condensation = scc_analyzer.create_condensation_graph(kosaraju_sccs)
    
    # Test with simple cycle
    print("\n6. Simple Cycle Test")
    print("-" * 25)
    cycle_analyzer = StronglyConnectedComponents(cycle_graph)
    cycle_sccs = cycle_analyzer.kosaraju_algorithm()
    
    print(f"Cycle graph SCCs: {cycle_sccs}")
    
    # Real-world example: Web page links
    print("\n7. Real-World Example: Web Page Links")
    print("-" * 45)
    
    web_graph = Graph(directed=True)
    web_graph.add_edge('home', 'about')
    web_graph.add_edge('about', 'contact')
    web_graph.add_edge('contact', 'about')  # Mutual links
    web_graph.add_edge('home', 'products')
    web_graph.add_edge('products', 'product1')
    web_graph.add_edge('product1', 'product2')
    web_graph.add_edge('product2', 'product1')  # Product pages link to each other
    web_graph.add_edge('contact', 'support')
    web_graph.add_vertex('blog')  # Isolated page
    
    print("Web page link graph:")
    web_graph.print_adjacency_list()
    
    web_analyzer = StronglyConnectedComponents(web_graph)
    web_sccs = web_analyzer.kosaraju_algorithm()
    
    print(f"\nWeb page SCCs: {web_sccs}")
    print("This shows which pages are strongly connected (can reach each other).")
    
    # Visual representation
    print("\n8. Visual Graph Representation")
    print("-" * 35)
    print("Original Graph:")
    print("    A -> B -> C")
    print("    ^    |    |")
    print("    |    v    v")
    print("    +----+    D -> E")
    print("              ^    |")
    print("              |    v")
    print("              +----+")
    print("                  |")
    print("                  v")
    print("                  F")
    print("                  G (isolated)")
    
    print(f"\nSCCs:")
    print("  SCC 1: A-B-C (cycle)")
    print("  SCC 2: D-E (cycle)")
    print("  SCC 3: F (single vertex)")
    print("  SCC 4: G (isolated)")
    
    # Algorithm complexity analysis
    print("\n9. Algorithm Complexity Analysis")
    print("-" * 40)
    print("Kosaraju's Algorithm:")
    print("  Time: O(V + E)")
    print("  Space: O(V)")
    print("  Advantages: Simple, easy to understand")
    
    print("\nTarjan's Algorithm:")
    print("  Time: O(V + E)")
    print("  Space: O(V) for recursion stack")
    print("  Advantages: Single pass, more efficient")


if __name__ == "__main__":
    demonstrate_scc_algorithms()
