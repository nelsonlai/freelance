"""
Focused Minimum Spanning Tree (MST) Implementation
Kruskal's and Prim's algorithms with detailed explanations
"""

from typing import List, Tuple, Set
from collections import defaultdict


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


class MST:
    """Minimum Spanning Tree algorithms implementation."""
    
    def __init__(self, edges: List[Tuple[str, str, float]], vertices: List[str] = None):
        """
        Initialize MST with edges and vertices.
        
        Args:
            edges: List of (u, v, weight) tuples
            vertices: List of all vertices (auto-detected if None)
        """
        self.edges = edges.copy()
        if vertices is None:
            self.vertices = set()
            for u, v, _ in edges:
                self.vertices.add(u)
                self.vertices.add(v)
            self.vertices = list(self.vertices)
        else:
            self.vertices = vertices
    
    def kruskal(self) -> Tuple[List[Tuple[str, str, float]], float]:
        """
        Kruskal's algorithm for MST.
        
        Returns:
            Tuple of (MST edges, total weight)
        """
        print("Kruskal's Algorithm for Minimum Spanning Tree")
        print("=" * 50)
        
        # Sort edges by weight
        sorted_edges = sorted(self.edges, key=lambda x: x[2])
        print(f"Edges sorted by weight: {sorted_edges}")
        
        # Initialize Union-Find
        uf = UnionFind(self.vertices)
        mst_edges = []
        total_weight = 0
        
        print(f"\nInitial components: {uf.components}")
        print("\nProcessing edges:")
        
        for i, (u, v, weight) in enumerate(sorted_edges):
            print(f"  Edge {i+1}: ({u}, {v}) weight {weight}")
            
            if uf.union(u, v):
                mst_edges.append((u, v, weight))
                total_weight += weight
                print(f"    ✓ Added to MST. Components remaining: {uf.components}")
            else:
                print(f"    ✗ Skipped (would create cycle)")
            
            # Stop if we have V-1 edges
            if len(mst_edges) == len(self.vertices) - 1:
                print(f"    MST complete with {len(mst_edges)} edges")
                break
        
        if uf.components > 1:
            print(f"Warning: Graph is not connected. {uf.components} components remain.")
        
        return mst_edges, total_weight
    
    def prim(self, start: str = None) -> Tuple[List[Tuple[str, str, float]], float]:
        """
        Prim's algorithm for MST.
        
        Args:
            start: Starting vertex (uses first vertex if None)
            
        Returns:
            Tuple of (MST edges, total weight)
        """
        if start is None:
            start = self.vertices[0]
        
        print(f"Prim's Algorithm for MST (starting from {start})")
        print("=" * 50)
        
        # Build adjacency list
        adj = defaultdict(list)
        for u, v, weight in self.edges:
            adj[u].append((v, weight))
            adj[v].append((u, weight))  # Undirected graph
        
        # Initialize
        mst_edges = []
        total_weight = 0
        in_mst = {start}
        candidate_edges = []  # (weight, u, v)
        
        # Add all edges from start vertex
        for neighbor, weight in adj[start]:
            candidate_edges.append((weight, start, neighbor))
        
        candidate_edges.sort()
        print(f"Initial candidate edges from {start}: {candidate_edges}")
        
        step = 1
        while len(in_mst) < len(self.vertices) and candidate_edges:
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
            for neighbor, edge_weight in adj[new_vertex]:
                if neighbor not in in_mst:
                    new_edges.append((edge_weight, new_vertex, neighbor))
            
            if new_edges:
                candidate_edges.extend(new_edges)
                candidate_edges.sort()
                print(f"    New candidate edges: {new_edges}")
            
            step += 1
        
        if len(in_mst) < len(self.vertices):
            print(f"Warning: Graph is not connected. Only {len(in_mst)} vertices in MST.")
        
        return mst_edges, total_weight
    
    def visualize_mst(self, mst_edges: List[Tuple[str, str, float]]) -> None:
        """Visualize the MST structure."""
        print(f"\nMST Visualization:")
        print(f"Total weight: {sum(weight for _, _, weight in mst_edges)}")
        print(f"Number of edges: {len(mst_edges)}")
        print(f"Number of vertices: {len(self.vertices)}")
        
        # Create adjacency representation of MST
        mst_adj = defaultdict(list)
        for u, v, weight in mst_edges:
            mst_adj[u].append((v, weight))
            mst_adj[v].append((u, weight))
        
        print(f"\nMST Structure:")
        for vertex in sorted(mst_adj.keys()):
            neighbors = mst_adj[vertex]
            neighbor_str = ", ".join([f"{n}({w})" for n, w in neighbors])
            print(f"  {vertex}: [{neighbor_str}]")
    
    def compare_algorithms(self) -> None:
        """Compare Kruskal and Prim algorithms."""
        print("\n" + "=" * 50)
        print("COMPARING KRUSKAL vs PRIM ALGORITHMS")
        print("=" * 50)
        
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


def demonstrate_mst():
    """Demonstrate MST algorithms with examples."""
    
    print("=" * 60)
    print("MINIMUM SPANNING TREE (MST) DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Simple graph
    print("\n1. Simple Graph Example")
    print("-" * 30)
    
    edges1 = [
        ('A', 'B', 4),
        ('A', 'C', 2),
        ('B', 'C', 1),
        ('B', 'D', 5),
        ('C', 'D', 8),
        ('C', 'E', 10),
        ('D', 'E', 2)
    ]
    
    print("Graph edges:", edges1)
    print("Visual representation:")
    print("    A --4-- B --5-- D")
    print("    |       |       |")
    print("    2       1       2")
    print("    |       |       |")
    print("    C --8-- D --10-- E")
    
    mst1 = MST(edges1)
    kruskal_edges, kruskal_weight = mst1.kruskal()
    
    print(f"\nKruskal MST Result:")
    print(f"  Edges: {kruskal_edges}")
    print(f"  Total weight: {kruskal_weight}")
    
    mst1.visualize_mst(kruskal_edges)
    
    # Example 2: Compare algorithms
    print("\n2. Algorithm Comparison")
    print("-" * 30)
    mst1.compare_algorithms()
    
    # Example 3: Real-world scenario
    print("\n3. Real-World Example: City Connections")
    print("-" * 45)
    
    city_edges = [
        ('NYC', 'Boston', 200),
        ('NYC', 'DC', 225),
        ('Boston', 'DC', 400),
        ('DC', 'Atlanta', 600),
        ('Atlanta', 'Miami', 650),
        ('NYC', 'Chicago', 800),
        ('Chicago', 'Denver', 1000),
        ('Denver', 'LA', 1000),
        ('LA', 'SanFran', 400)
    ]
    
    print("City connection costs (in miles):")
    for u, v, w in city_edges:
        print(f"  {u} <-> {v}: {w} miles")
    
    city_mst = MST(city_edges)
    city_edges_result, city_weight = city_mst.kruskal()
    
    print(f"\nMinimum cost network:")
    total_cost = 0
    for u, v, w in city_edges_result:
        print(f"  {u} <-> {v}: {w} miles")
        total_cost += w
    
    print(f"Total cost: {total_cost} miles")
    
    # Example 4: Disconnected graph
    print("\n4. Disconnected Graph Test")
    print("-" * 35)
    
    disconnected_edges = [
        ('A', 'B', 3),
        ('C', 'D', 2),
        ('E', 'F', 1)
    ]
    
    print("Disconnected graph edges:", disconnected_edges)
    disconnected_mst = MST(disconnected_edges)
    disconnected_result, disconnected_weight = disconnected_mst.kruskal()
    
    print(f"Result: {disconnected_result}")
    print(f"Weight: {disconnected_weight}")
    print("Note: This creates a forest (multiple trees) since graph is disconnected.")
    
    # Algorithm complexity
    print("\n5. Algorithm Complexity Analysis")
    print("-" * 40)
    print("Kruskal's Algorithm:")
    print("  Time: O(E log E) = O(E log V)")
    print("  Space: O(V) for Union-Find")
    print("  Best for: Sparse graphs")
    
    print("\nPrim's Algorithm:")
    print("  Time: O(E log V) with binary heap")
    print("  Space: O(V) for priority queue")
    print("  Best for: Dense graphs")
    
    print("\nWhen to use which:")
    print("  - Use Kruskal when graph is sparse (E << V²)")
    print("  - Use Prim when graph is dense (E ≈ V²)")
    print("  - Both give the same optimal result!")


if __name__ == "__main__":
    demonstrate_mst()
