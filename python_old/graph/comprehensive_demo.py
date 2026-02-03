"""
Comprehensive Graph Algorithms Demonstration
Main program that showcases all graph algorithms with interactive examples
"""

import sys
import os
from typing import Dict, List, Tuple, Optional

# Add current directory to path for imports
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from graph_class import Graph, create_sample_graphs
from graph_traversal import GraphTraversal
from shortest_path import ShortestPath
from minimum_spanning_tree import MinimumSpanningTree
from topological_sort import TopologicalSort
from strongly_connected_components import StronglyConnectedComponents


class GraphAlgorithmsDemo:
    """Main demonstration class for all graph algorithms."""
    
    def __init__(self):
        self.graphs = {}
        self.setup_sample_graphs()
    
    def setup_sample_graphs(self):
        """Create various sample graphs for demonstration."""
        
        # 1. Simple undirected graph for BFS/DFS
        self.graphs['simple_undirected'] = Graph(directed=False)
        self.graphs['simple_undirected'].add_edge('A', 'B', 1)
        self.graphs['simple_undirected'].add_edge('A', 'C', 2)
        self.graphs['simple_undirected'].add_edge('B', 'D', 3)
        self.graphs['simple_undirected'].add_edge('C', 'D', 1)
        self.graphs['simple_undirected'].add_edge('C', 'E', 4)
        self.graphs['simple_undirected'].add_edge('D', 'E', 2)
        
        # 2. Directed graph for topological sort
        self.graphs['dag'] = Graph(directed=True)
        self.graphs['dag'].add_edge('A', 'B')
        self.graphs['dag'].add_edge('A', 'C')
        self.graphs['dag'].add_edge('B', 'D')
        self.graphs['dag'].add_edge('C', 'D')
        self.graphs['dag'].add_edge('C', 'E')
        self.graphs['dag'].add_edge('D', 'F')
        self.graphs['dag'].add_edge('E', 'F')
        
        # 3. Weighted graph for shortest path
        self.graphs['weighted'] = Graph(directed=True)
        self.graphs['weighted'].add_edge('A', 'B', 4)
        self.graphs['weighted'].add_edge('A', 'C', 2)
        self.graphs['weighted'].add_edge('B', 'C', 1)
        self.graphs['weighted'].add_edge('B', 'D', 5)
        self.graphs['weighted'].add_edge('C', 'D', 8)
        self.graphs['weighted'].add_edge('C', 'E', 10)
        self.graphs['weighted'].add_edge('D', 'E', 2)
        
        # 4. Graph with negative weights
        self.graphs['negative_weights'] = Graph(directed=True)
        self.graphs['negative_weights'].add_edge('A', 'B', 4)
        self.graphs['negative_weights'].add_edge('A', 'C', 2)
        self.graphs['negative_weights'].add_edge('B', 'C', -3)
        self.graphs['negative_weights'].add_edge('B', 'D', 5)
        self.graphs['negative_weights'].add_edge('C', 'D', 1)
        self.graphs['negative_weights'].add_edge('D', 'E', 2)
        self.graphs['negative_weights'].add_edge('E', 'B', -1)
        
        # 5. Graph for MST
        self.graphs['mst_graph'] = Graph(directed=False)
        self.graphs['mst_graph'].add_edge('A', 'B', 4)
        self.graphs['mst_graph'].add_edge('A', 'C', 2)
        self.graphs['mst_graph'].add_edge('B', 'C', 1)
        self.graphs['mst_graph'].add_edge('B', 'D', 5)
        self.graphs['mst_graph'].add_edge('C', 'D', 8)
        self.graphs['mst_graph'].add_edge('C', 'E', 10)
        self.graphs['mst_graph'].add_edge('D', 'E', 2)
        
        # 6. Graph with cycles for SCC
        self.graphs['scc_graph'] = Graph(directed=True)
        self.graphs['scc_graph'].add_edge('A', 'B')
        self.graphs['scc_graph'].add_edge('B', 'C')
        self.graphs['scc_graph'].add_edge('C', 'A')  # Cycle A-B-C
        self.graphs['scc_graph'].add_edge('C', 'D')
        self.graphs['scc_graph'].add_edge('D', 'E')
        self.graphs['scc_graph'].add_edge('E', 'D')  # Cycle D-E
        self.graphs['scc_graph'].add_vertex('F')  # Isolated vertex
    
    def display_menu(self):
        """Display the main menu."""
        print("\n" + "=" * 70)
        print("COMPREHENSIVE GRAPH ALGORITHMS DEMONSTRATION")
        print("=" * 70)
        print("1. Graph Representations")
        print("2. Graph Traversal (BFS & DFS)")
        print("3. Shortest Path Algorithms")
        print("4. Minimum Spanning Tree")
        print("5. Topological Sorting")
        print("6. Strongly Connected Components")
        print("7. Run All Demonstrations")
        print("8. Interactive Graph Builder")
        print("9. Exit")
        print("-" * 70)
    
    def demonstrate_graph_representations(self):
        """Demonstrate different graph representations."""
        print("\n" + "=" * 50)
        print("GRAPH REPRESENTATIONS DEMONSTRATION")
        print("=" * 50)
        
        # Create a sample graph
        graph = Graph(directed=False)
        graph.add_edge('A', 'B', 3)
        graph.add_edge('A', 'C', 1)
        graph.add_edge('B', 'D', 2)
        graph.add_edge('C', 'D', 4)
        
        print("Sample Graph:")
        print("    A --3-- B")
        print("    |       |")
        print("    1       2")
        print("    |       |")
        print("    C --4-- D")
        
        print(f"\nGraph Info: {graph}")
        
        print("\nAdjacency List Representation:")
        graph.print_adjacency_list()
        
        print("\nAdjacency Matrix Representation:")
        graph.print_adjacency_matrix()
        
        print(f"\nGraph Properties:")
        print(f"  Vertices: {graph.get_all_vertices()}")
        print(f"  Edges: {graph.get_all_edges()}")
        print(f"  Is connected: {graph.is_connected()}")
        print(f"  Vertex degrees: {[f'{v}:{graph.get_vertex_degree(v)}' for v in graph.get_all_vertices()]}")
    
    def demonstrate_traversal(self):
        """Demonstrate BFS and DFS algorithms."""
        print("\n" + "=" * 50)
        print("GRAPH TRAVERSAL DEMONSTRATION")
        print("=" * 50)
        
        graph = self.graphs['simple_undirected']
        print("Graph Structure:")
        graph.print_adjacency_list()
        
        traversal = GraphTraversal(graph)
        
        # BFS demonstration
        print("\nBreadth-First Search (BFS):")
        print("-" * 30)
        bfs_result = traversal.bfs('A')
        print(f"BFS Order: {bfs_result['traversal_order']}")
        print(f"Distances: {bfs_result['distances']}")
        
        # DFS demonstration
        print("\nDepth-First Search (DFS):")
        print("-" * 30)
        dfs_result = traversal.dfs('A')
        print(f"DFS Order: {dfs_result['traversal_order']}")
        print(f"Discovery Times: {dfs_result['discovery_time']}")
        print(f"Finish Times: {dfs_result['finish_time']}")
        
        # Path finding
        print("\nPath Finding:")
        print("-" * 15)
        path_bfs = traversal.find_path('A', 'E', use_bfs=True)
        path_dfs = traversal.find_path('A', 'E', use_bfs=False)
        print(f"Path A->E (BFS): {' -> '.join(path_bfs)}")
        print(f"Path A->E (DFS): {' -> '.join(path_dfs)}")
        
        # Cycle detection
        print(f"\nCycle Detection: {traversal.detect_cycle()}")
        
        # Connected components
        components = traversal.find_connected_components()
        print(f"Connected Components: {components}")
    
    def demonstrate_shortest_path(self):
        """Demonstrate shortest path algorithms."""
        print("\n" + "=" * 50)
        print("SHORTEST PATH DEMONSTRATION")
        print("=" * 50)
        
        # Dijkstra's algorithm
        print("Dijkstra's Algorithm (Non-negative weights):")
        print("-" * 50)
        dijkstra_graph = self.graphs['weighted']
        print("Graph:")
        dijkstra_graph.print_adjacency_list()
        
        sp = ShortestPath(dijkstra_graph)
        distances, previous = sp.dijkstra('A')
        
        print(f"\nShortest distances from A: {distances}")
        print(f"Previous vertices: {previous}")
        
        # Find specific paths
        print("\nShortest paths from A:")
        for vertex in dijkstra_graph.vertices:
            if vertex != 'A':
                path = sp.reconstruct_path('A', vertex, previous)
                if path:
                    print(f"  A -> {vertex}: {' -> '.join(path)} (distance: {distances[vertex]})")
        
        # Bellman-Ford algorithm
        print("\nBellman-Ford Algorithm (Handles negative weights):")
        print("-" * 55)
        bellman_graph = self.graphs['negative_weights']
        print("Graph with negative weights:")
        bellman_graph.print_adjacency_list()
        
        sp_neg = ShortestPath(bellman_graph)
        distances_neg, previous_neg, has_cycle = sp_neg.bellman_ford('A')
        
        print(f"\nShortest distances from A: {distances_neg}")
        print(f"Has negative cycle: {has_cycle}")
    
    def demonstrate_mst(self):
        """Demonstrate minimum spanning tree algorithms."""
        print("\n" + "=" * 50)
        print("MINIMUM SPANNING TREE DEMONSTRATION")
        print("=" * 50)
        
        graph = self.graphs['mst_graph']
        print("Graph:")
        graph.print_adjacency_list()
        
        mst = MinimumSpanningTree(graph)
        
        # Kruskal's algorithm
        print("\nKruskal's Algorithm:")
        print("-" * 25)
        kruskal_edges, kruskal_weight = mst.kruskal()
        print(f"MST Edges: {kruskal_edges}")
        print(f"Total Weight: {kruskal_weight}")
        
        # Prim's algorithm
        print("\nPrim's Algorithm:")
        print("-" * 20)
        prim_edges, prim_weight = mst.prim('A')
        print(f"MST Edges: {prim_edges}")
        print(f"Total Weight: {prim_weight}")
        
        # Visualize MST
        mst.visualize_mst(kruskal_edges)
    
    def demonstrate_topological_sort(self):
        """Demonstrate topological sorting algorithms."""
        print("\n" + "=" * 50)
        print("TOPOLOGICAL SORTING DEMONSTRATION")
        print("=" * 50)
        
        graph = self.graphs['dag']
        print("DAG (Directed Acyclic Graph):")
        graph.print_adjacency_list()
        
        ts = TopologicalSort(graph)
        
        # Kahn's algorithm
        print("\nKahn's Algorithm:")
        print("-" * 20)
        kahn_order, kahn_cycle = ts.kahn_algorithm()
        if not kahn_cycle:
            print(f"Topological Order: {' -> '.join(kahn_order)}")
        
        # DFS algorithm
        print("\nDFS Algorithm:")
        print("-" * 15)
        dfs_order, dfs_cycle = ts.dfs_algorithm()
        if not dfs_cycle:
            print(f"Topological Order: {' -> '.join(dfs_order)}")
        
        # Real-world example
        print("\nReal-world Example: Course Prerequisites")
        print("-" * 45)
        course_graph = Graph(directed=True)
        course_graph.add_edge('CS101', 'CS102')
        course_graph.add_edge('CS102', 'CS201')
        course_graph.add_edge('CS201', 'CS301')
        course_graph.add_edge('MATH101', 'CS201')
        course_graph.add_edge('MATH101', 'MATH201')
        
        course_ts = TopologicalSort(course_graph)
        course_order, course_cycle = course_ts.kahn_algorithm()
        
        if not course_cycle:
            print(f"Valid course sequence: {' -> '.join(course_order)}")
    
    def demonstrate_scc(self):
        """Demonstrate strongly connected components algorithms."""
        print("\n" + "=" * 50)
        print("STRONGLY CONNECTED COMPONENTS DEMONSTRATION")
        print("=" * 50)
        
        graph = self.graphs['scc_graph']
        print("Graph with cycles:")
        graph.print_adjacency_list()
        
        scc_analyzer = StronglyConnectedComponents(graph)
        
        # Kosaraju's algorithm
        print("\nKosaraju's Algorithm:")
        print("-" * 25)
        kosaraju_sccs = scc_analyzer.kosaraju_algorithm()
        scc_analyzer.analyze_scc_properties(kosaraju_sccs)
        
        # Tarjan's algorithm
        print("\nTarjan's Algorithm:")
        print("-" * 20)
        tarjan_sccs = scc_analyzer.tarjan_algorithm()
        scc_analyzer.analyze_scc_properties(tarjan_sccs)
        
        # Create condensation graph
        condensation = scc_analyzer.create_condensation_graph(kosaraju_sccs)
    
    def run_all_demonstrations(self):
        """Run all algorithm demonstrations."""
        print("\n" + "=" * 70)
        print("RUNNING ALL GRAPH ALGORITHM DEMONSTRATIONS")
        print("=" * 70)
        
        self.demonstrate_graph_representations()
        self.demonstrate_traversal()
        self.demonstrate_shortest_path()
        self.demonstrate_mst()
        self.demonstrate_topological_sort()
        self.demonstrate_scc()
        
        print("\n" + "=" * 70)
        print("ALL DEMONSTRATIONS COMPLETED")
        print("=" * 70)
    
    def interactive_graph_builder(self):
        """Interactive graph builder and algorithm tester."""
        print("\n" + "=" * 50)
        print("INTERACTIVE GRAPH BUILDER")
        print("=" * 50)
        
        directed = input("Create directed graph? (y/n): ").lower() == 'y'
        graph = Graph(directed=directed)
        
        print(f"\nCreated {'directed' if directed else 'undirected'} graph")
        print("Commands: add_vertex <name>, add_edge <u> <v> [weight], show, exit")
        
        while True:
            command = input("\nEnter command: ").strip().split()
            
            if not command:
                continue
            
            if command[0] == 'exit':
                break
            elif command[0] == 'add_vertex' and len(command) == 2:
                graph.add_vertex(command[1])
                print(f"Added vertex {command[1]}")
            elif command[0] == 'add_edge' and len(command) >= 3:
                weight = float(command[3]) if len(command) > 3 else 1.0
                graph.add_edge(command[1], command[2], weight)
                print(f"Added edge {command[1]} -> {command[2]} (weight: {weight})")
            elif command[0] == 'show':
                print(f"\nGraph: {graph}")
                graph.print_adjacency_list()
            else:
                print("Invalid command. Use: add_vertex <name>, add_edge <u> <v> [weight], show, exit")
    
    def run(self):
        """Main program loop."""
        while True:
            self.display_menu()
            choice = input("Enter your choice (1-9): ").strip()
            
            try:
                if choice == '1':
                    self.demonstrate_graph_representations()
                elif choice == '2':
                    self.demonstrate_traversal()
                elif choice == '3':
                    self.demonstrate_shortest_path()
                elif choice == '4':
                    self.demonstrate_mst()
                elif choice == '5':
                    self.demonstrate_topological_sort()
                elif choice == '6':
                    self.demonstrate_scc()
                elif choice == '7':
                    self.run_all_demonstrations()
                elif choice == '8':
                    self.interactive_graph_builder()
                elif choice == '9':
                    print("Thank you for using the Graph Algorithms Demo!")
                    break
                else:
                    print("Invalid choice. Please enter 1-9.")
                
                input("\nPress Enter to continue...")
                
            except KeyboardInterrupt:
                print("\n\nProgram interrupted. Goodbye!")
                break
            except Exception as e:
                print(f"\nError: {e}")
                input("Press Enter to continue...")


def main():
    """Main function."""
    print("Welcome to the Comprehensive Graph Algorithms Demonstration!")
    print("This program showcases various graph algorithms with detailed explanations.")
    
    demo = GraphAlgorithmsDemo()
    demo.run()


if __name__ == "__main__":
    main()
