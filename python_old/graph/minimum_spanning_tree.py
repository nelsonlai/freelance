"""
Minimum Spanning Tree Algorithms: Kruskal and Prim
Demonstrates MST algorithms with Union-Find data structure
"""

from typing import List, Tuple, Set, Dict
from graph_class import Graph


class UnionFind:
    """Union-Find data structure for Kruskal's algorithm."""
    
    def __init__(self, vertices: List[str]):
        self.parent = {v: v for v in vertices}
        self.rank = {v: 0 for v in vertices}
        self.components = len(vertices)
    
    def find(self, x: str) -> str:
        """Find root of x with path compression."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x: str, y: str) -> bool:
        """Union sets containing x and y. Returns True if union was performed."""
        px, py = self.find(x), self.find(y)
        if px == py:
            return False  # Already in same set
        
        # Union by rank
        if self.rank[px] < self.rank[py]:
            self.parent[px] = py
        elif self.rank[px] > self.rank[py]:
            self.parent[py] = px
        else:
            self.parent[py] = px
            self.rank[px] += 1
        
        self.components -= 1
        return True
    
    def connected(self, x: str, y: str) -> bool:
        """Check if x and y are in the same component."""
        return self.find(x) == self.find(y)
    
    def get_components(self) -> int:
        """Get number of connected components."""
        return self.components


class MinimumSpanningTree:
    """Class containing MST algorithm implementations."""
    
    def __init__(self, graph: Graph):
        if graph.directed:
            raise ValueError("MST algorithms only work on undirected graphs")
        self.graph = graph
    
    def kruskal(self) -> Tuple[List[Tuple[str, str, float]], float]:
        """
        Kruskal's algorithm for finding MST.
        
        Returns:
            Tuple of (MST edges, total weight)
        """
        print("Kruskal's Algorithm for Minimum Spanning Tree")
        print("=" * 50)
        
        # Sort edges by weight
        edges = sorted(self.graph.get_all_edges(), key=lambda x: x[2])
        print(f"Edges sorted by weight: {edges}")
        
        # Initialize Union-Find
        uf = UnionFind(list(self.graph.vertices))
        mst_edges = []
        total_weight = 0
        
        print(f"\nInitial components: {uf.get_components()}")
        print("\nProcessing edges:")
        
        for i, (u, v, weight) in enumerate(edges):
            print(f"  Edge {i+1}: ({u}, {v}) weight {weight}")
            
            if uf.union(u, v):
                mst_edges.append((u, v, weight))
                total_weight += weight
                print(f"    Added to MST. Components remaining: {uf.get_components()}")
            else:
                print(f"    Skipped (would create cycle)")
            
            # Stop if we have V-1 edges
            if len(mst_edges) == len(self.graph.vertices) - 1:
                print(f"    MST complete with {len(mst_edges)} edges")
                break
        
        if uf.get_components() > 1:
            print(f"Warning: Graph is not connected. {uf.get_components()} components remain.")
        
        return mst_edges, total_weight
    
    def prim(self, start: str = None) -> Tuple[List[Tuple[str, str, float]], float]:
        """
        Prim's algorithm for finding MST.
        
        Args:
            start: Starting vertex (if None, uses first vertex)
            
        Returns:
            Tuple of (MST edges, total weight)
        """
        if start is None:
            start = next(iter(self.graph.vertices))
        
        if start not in self.graph.vertices:
            raise ValueError(f"Vertex {start} not in graph")
        
        print(f"Prim's Algorithm for Minimum Spanning Tree (starting from {start})")
        print("=" * 60)
        
        # Initialize
        mst_edges = []
        total_weight = 0
        in_mst = {start}
        candidate_edges = []  # (weight, u, v)
        
        # Add all edges from start vertex
        for neighbor, weight in self.graph.get_neighbors(start):
            candidate_edges.append((weight, start, neighbor))
        
        candidate_edges.sort()  # Sort by weight
        print(f"Initial candidate edges from {start}: {candidate_edges}")
        
        step = 1
        while len(in_mst) < len(self.graph.vertices) and candidate_edges:
            # Find minimum weight edge
            weight, u, v = candidate_edges.pop(0)
            
            # Skip if both vertices already in MST
            if u in in_mst and v in in_mst:
                print(f"  Step {step}: Edge ({u}, {v}) skipped (both vertices in MST)")
                continue
            
            # Add edge to MST
            mst_edges.append((u, v, weight))
            total_weight += weight
            
            # Add new vertex to MST
            new_vertex = v if u in in_mst else u
            in_mst.add(new_vertex)
            
            print(f"  Step {step}: Added edge ({u}, {v}) weight {weight}")
            print(f"    MST vertices: {sorted(in_mst)}")
            
            # Add new candidate edges from new vertex
            new_edges = []
            for neighbor, edge_weight in self.graph.get_neighbors(new_vertex):
                if neighbor not in in_mst:
                    new_edges.append((edge_weight, new_vertex, neighbor))
            
            if new_edges:
                candidate_edges.extend(new_edges)
                candidate_edges.sort()
                print(f"    New candidate edges: {new_edges}")
            
            step += 1
        
        if len(in_mst) < len(self.graph.vertices):
            print(f"Warning: Graph is not connected. Only {len(in_mst)} vertices in MST.")
        
        return mst_edges, total_weight
    
    def compare_algorithms(self) -> None:
        """Compare Kruskal and Prim algorithms on the same graph."""
        print("\n" + "=" * 60)
        print("COMPARING KRUSKAL vs PRIM ALGORITHMS")
        print("=" * 60)
        
        # Run both algorithms
        kruskal_edges, kruskal_weight = self.kruskal()
        print("\n" + "-" * 40)
        prim_edges, prim_weight = self.prim()
        
        # Compare results
        print(f"\nComparison Results:")
        print(f"  Kruskal MST weight: {kruskal_weight}")
        print(f"  Prim MST weight: {prim_weight}")
        print(f"  Weights match: {kruskal_weight == prim_weight}")
        
        print(f"\nKruskal MST edges: {kruskal_edges}")
        print(f"Prim MST edges: {prim_edges}")
        
        # Check if both algorithms found the same MST
        kruskal_set = set((min(u, v), max(u, v), w) for u, v, w in kruskal_edges)
        prim_set = set((min(u, v), max(u, v), w) for u, v, w in prim_edges)
        
        print(f"  Same MST found: {kruskal_set == prim_set}")
    
    def visualize_mst(self, mst_edges: List[Tuple[str, str, float]]) -> None:
        """Visualize the MST structure."""
        print(f"\nMST Visualization:")
        print(f"Total weight: {sum(weight for _, _, weight in mst_edges)}")
        print(f"Number of edges: {len(mst_edges)}")
        print(f"Number of vertices: {len(self.graph.vertices)}")
        
        # Create adjacency representation of MST
        mst_adj = {}
        for u, v, weight in mst_edges:
            if u not in mst_adj:
                mst_adj[u] = []
            if v not in mst_adj:
                mst_adj[v] = []
            mst_adj[u].append((v, weight))
            mst_adj[v].append((u, weight))
        
        print(f"\nMST Structure:")
        for vertex in sorted(mst_adj.keys()):
            neighbors = mst_adj[vertex]
            neighbor_str = ", ".join([f"{n}({w})" for n, w in neighbors])
            print(f"  {vertex}: [{neighbor_str}]")


def demonstrate_mst_algorithms():
    """Demonstrate MST algorithms with examples."""
    
    print("=" * 70)
    print("MINIMUM SPANNING TREE ALGORITHMS DEMONSTRATION")
    print("=" * 70)
    
    # Create sample graphs
    print("\n1. Creating Sample Graphs")
    print("-" * 30)
    
    # Graph 1: Simple connected graph
    graph1 = Graph(directed=False)
    graph1.add_edge('A', 'B', 4)
    graph1.add_edge('A', 'C', 2)
    graph1.add_edge('B', 'C', 1)
    graph1.add_edge('B', 'D', 5)
    graph1.add_edge('C', 'D', 8)
    graph1.add_edge('C', 'E', 10)
    graph1.add_edge('D', 'E', 2)
    
    print("Graph 1 (Connected):")
    graph1.print_adjacency_list()
    
    # Graph 2: Disconnected graph
    graph2 = Graph(directed=False)
    graph2.add_edge('A', 'B', 3)
    graph2.add_edge('C', 'D', 2)
    graph2.add_vertex('E')  # Isolated vertex
    
    print("\nGraph 2 (Disconnected):")
    graph2.print_adjacency_list()
    
    # Demonstrate Kruskal's algorithm
    print("\n2. Kruskal's Algorithm")
    print("-" * 30)
    mst1 = MinimumSpanningTree(graph1)
    kruskal_edges, kruskal_weight = mst1.kruskal()
    
    print(f"\nKruskal MST Result:")
    print(f"  Edges: {kruskal_edges}")
    print(f"  Total weight: {kruskal_weight}")
    
    mst1.visualize_mst(kruskal_edges)
    
    # Demonstrate Prim's algorithm
    print("\n3. Prim's Algorithm")
    print("-" * 25)
    prim_edges, prim_weight = mst1.prim('A')
    
    print(f"\nPrim MST Result:")
    print(f"  Edges: {prim_edges}")
    print(f"  Total weight: {prim_weight}")
    
    mst1.visualize_mst(prim_edges)
    
    # Compare algorithms
    print("\n4. Algorithm Comparison")
    print("-" * 30)
    mst1.compare_algorithms()
    
    # Test with disconnected graph
    print("\n5. Disconnected Graph Test")
    print("-" * 35)
    mst2 = MinimumSpanningTree(graph2)
    
    try:
        kruskal_edges2, kruskal_weight2 = mst2.kruskal()
        print(f"Kruskal on disconnected graph: {kruskal_edges2}, weight: {kruskal_weight2}")
    except Exception as e:
        print(f"Error with disconnected graph: {e}")
    
    # Visual representation
    print("\n6. Visual Graph Representation")
    print("-" * 35)
    print("Original Graph:")
    print("    A --4-- B --5-- D")
    print("    |       |       |")
    print("    2       1       2")
    print("    |       |       |")
    print("    C --10-- E -----+")
    print("    |")
    print("    8")
    print("    |")
    print("    D")
    
    print(f"\nMST (weight {kruskal_weight}):")
    print("    A --2-- C")
    print("    |")
    print("    B --1-- C")
    print("    |")
    print("    B --5-- D --2-- E")
    
    # Algorithm complexity analysis
    print("\n7. Algorithm Complexity Analysis")
    print("-" * 40)
    print("Kruskal's Algorithm:")
    print("  Time: O(E log E) = O(E log V)")
    print("  Space: O(V) for Union-Find")
    print("  Best for: Sparse graphs")
    
    print("\nPrim's Algorithm:")
    print("  Time: O(E log V) with binary heap")
    print("  Space: O(V) for priority queue")
    print("  Best for: Dense graphs")


if __name__ == "__main__":
    demonstrate_mst_algorithms()
