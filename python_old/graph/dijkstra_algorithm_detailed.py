"""
Dijkstra's Algorithm - Comprehensive Implementation with Educational Comments

This module provides a detailed implementation of Dijkstra's algorithm for finding
shortest paths in weighted graphs with non-negative edge weights.

Educational Goals:
1. Understand the greedy nature of Dijkstra's algorithm
2. Learn how priority queues optimize the algorithm
3. See step-by-step execution with detailed tracking
4. Understand when and why to use Dijkstra's algorithm
5. Learn to implement and debug shortest path algorithms

Real-World Applications:
- GPS navigation systems
- Network routing protocols
- Social network analysis
- Game AI pathfinding
- Resource allocation optimization
"""

import heapq
import time
from typing import Dict, List, Tuple, Optional, Set
from collections import defaultdict
from dataclasses import dataclass
from enum import Enum


class VertexStatus(Enum):
    """
    Status tracking for vertices during Dijkstra's algorithm execution.
    
    Educational Purpose:
    - UNVISITED: Vertex not yet processed (initial state)
    - IN_QUEUE: Vertex in priority queue (candidate for processing)
    - PROCESSED: Vertex completely processed (final shortest path found)
    
    This helps visualize the algorithm's progress and understand
    which vertices are being considered at each step.
    """
    UNVISITED = "UNVISITED"
    IN_QUEUE = "IN_QUEUE"
    PROCESSED = "PROCESSED"


@dataclass
class DijkstraResult:
    """
    Comprehensive result structure for Dijkstra's algorithm.
    
    Educational Purpose:
    - Encapsulates all information returned by the algorithm
    - Makes it easy to analyze results and perform further operations
    - Provides clear interface for testing and debugging
    """
    distances: Dict[str, float]
    previous: Dict[str, Optional[str]]
    execution_time: float
    vertices_processed: int
    total_vertices: int
    path_found: Dict[str, bool]
    algorithm_steps: List[Dict]


class DijkstraAlgorithm:
    """
    Comprehensive Dijkstra's algorithm implementation with educational features.
    
    Educational Goals:
    1. Understand greedy algorithm principles
    2. Learn priority queue usage for optimization
    3. See step-by-step algorithm execution
    4. Understand edge relaxation concept
    5. Learn path reconstruction techniques
    6. Understand complexity analysis
    
    Key Features:
    - Step-by-step execution tracking
    - Detailed logging for educational purposes
    - Multiple priority queue implementations
    - Path reconstruction functionality
    - Performance analysis and timing
    - Visualization of algorithm progress
    """
    
    def __init__(self, graph: Dict[str, List[Tuple[str, float]]], debug: bool = True):
        """
        Initialize Dijkstra's algorithm with graph representation.
        
        Args:
            graph: Adjacency list representation where graph[u] contains
                   list of (neighbor, weight) tuples for vertex u
            debug: Enable detailed logging for educational purposes
            
        Educational Notes:
        - Adjacency list is efficient for sparse graphs
        - Weight information is preserved for shortest path calculation
        - Debug mode provides step-by-step execution details
        
        Time Complexity: O(1) - just initialization
        Space Complexity: O(1) - no additional space used
        """
        self.graph = graph
        self.debug = debug
        self.vertices = set(graph.keys())
        
        # Add all vertices that appear as neighbors
        for neighbors in graph.values():
            for neighbor, _ in neighbors:
                self.vertices.add(neighbor)
        
        if self.debug:
            print(f"Dijkstra's Algorithm initialized with {len(self.vertices)} vertices")
            print("Graph representation:")
            for vertex in sorted(self.vertices):
                if vertex in graph:
                    neighbors = graph[vertex]
                    neighbor_str = ", ".join([f"{n}({w})" for n, w in neighbors])
                    print(f"  {vertex}: [{neighbor_str}]")
                else:
                    print(f"  {vertex}: []")
    
    def dijkstra_binary_heap(self, start: str) -> DijkstraResult:
        """
        Dijkstra's algorithm implementation using binary heap (most common).
        
        Algorithm Steps:
        1. Initialize distances: dist[start] = 0, others = infinity
        2. Create priority queue with all vertices
        3. Extract vertex with minimum distance
        4. Relax all edges from current vertex
        5. Update distances and add to queue if improved
        6. Repeat until queue is empty
        
        Args:
            start: Source vertex for shortest path calculation
            
        Returns:
            DijkstraResult containing distances, previous vertices, and execution details
            
        Time Complexity: O((V + E) log V) where V is vertices, E is edges
        Space Complexity: O(V) for priority queue and distance tracking
        
        Educational Benefits:
        - Shows greedy algorithm in action
        - Demonstrates priority queue usage
        - Illustrates edge relaxation concept
        - Provides step-by-step execution tracking
        """
        if self.debug:
            print(f"\n{'='*60}")
            print(f"DIJKSTRA'S ALGORITHM (Binary Heap Implementation)")
            print(f"Starting from vertex: {start}")
            print(f"{'='*60}")
        
        start_time = time.time()
        
        # Step 1: Initialize data structures
        distances = {vertex: float('infinity') for vertex in self.vertices}
        previous = {vertex: None for vertex in self.vertices}
        status = {vertex: VertexStatus.UNVISITED for vertex in self.vertices}
        
        # Set source distance to 0
        distances[start] = 0
        status[start] = VertexStatus.IN_QUEUE
        
        # Priority queue: (distance, vertex)
        # Using tuple for comparison (distance is primary key)
        priority_queue = [(0, start)]
        heapq.heapify(priority_queue)
        
        # Tracking for educational purposes
        algorithm_steps = []
        vertices_processed = 0
        
        if self.debug:
            print(f"\nInitialization:")
            print(f"  Source vertex: {start}")
            print(f"  Initial distances: {distances}")
            print(f"  Priority queue: {priority_queue}")
        
        # Step 2: Main algorithm loop
        while priority_queue:
            # Extract vertex with minimum distance
            current_distance, current_vertex = heapq.heappop(priority_queue)
            
            # Skip if vertex already processed (duplicate entries in queue)
            if status[current_vertex] == VertexStatus.PROCESSED:
                if self.debug:
                    print(f"\nSkipping {current_vertex} (already processed)")
                continue
            
            # Mark vertex as processed
            status[current_vertex] = VertexStatus.PROCESSED
            vertices_processed += 1
            
            if self.debug:
                print(f"\nStep {vertices_processed}: Processing vertex {current_vertex}")
                print(f"  Distance from source: {current_distance}")
                print(f"  Status: {status[current_vertex].value}")
            
            # Step 3: Relax all edges from current vertex
            edges_relaxed = []
            if current_vertex in self.graph:
                for neighbor, edge_weight in self.graph[current_vertex]:
                    # Skip if neighbor already processed
                    if status[neighbor] == VertexStatus.PROCESSED:
                        continue
                    
                    # Calculate new distance through current vertex
                    new_distance = current_distance + edge_weight
                    
                    # Relaxation: update if new path is shorter
                    if new_distance < distances[neighbor]:
                        old_distance = distances[neighbor]
                        distances[neighbor] = new_distance
                        previous[neighbor] = current_vertex
                        
                        # Add to priority queue (may create duplicates, handled above)
                        heapq.heappush(priority_queue, (new_distance, neighbor))
                        status[neighbor] = VertexStatus.IN_QUEUE
                        
                        edges_relaxed.append({
                            'neighbor': neighbor,
                            'edge_weight': edge_weight,
                            'old_distance': old_distance,
                            'new_distance': new_distance,
                            'improvement': old_distance - new_distance
                        })
                        
                        if self.debug:
                            print(f"    Relaxed edge to {neighbor}: {old_distance} → {new_distance}")
                            print(f"    Added {neighbor} to queue with distance {new_distance}")
                    else:
                        if self.debug:
                            print(f"    Edge to {neighbor}: no improvement ({distances[neighbor]} ≤ {new_distance})")
            
            # Record step for analysis
            algorithm_steps.append({
                'step': vertices_processed,
                'current_vertex': current_vertex,
                'current_distance': current_distance,
                'edges_relaxed': edges_relaxed,
                'queue_size': len(priority_queue),
                'distances': distances.copy()
            })
            
            if self.debug and edges_relaxed:
                print(f"  Edges relaxed: {len(edges_relaxed)}")
                for edge in edges_relaxed:
                    print(f"    {current_vertex} → {edge['neighbor']}: "
                          f"{edge['old_distance']} → {edge['new_distance']} "
                          f"(improvement: {edge['improvement']:.1f})")
        
        execution_time = time.time() - start_time
        
        # Determine which vertices have paths from source
        path_found = {}
        for vertex in self.vertices:
            path_found[vertex] = distances[vertex] != float('infinity')
        
        # Create comprehensive result
        result = DijkstraResult(
            distances=distances,
            previous=previous,
            execution_time=execution_time,
            vertices_processed=vertices_processed,
            total_vertices=len(self.vertices),
            path_found=path_found,
            algorithm_steps=algorithm_steps
        )
        
        if self.debug:
            print(f"\n{'='*60}")
            print("DIJKSTRA'S ALGORITHM COMPLETED")
            print(f"{'='*60}")
            print(f"Execution Summary:")
            print(f"  Vertices processed: {vertices_processed}/{len(self.vertices)}")
            print(f"  Execution time: {execution_time:.6f} seconds")
            print(f"  Algorithm steps: {len(algorithm_steps)}")
            
            print(f"\nFinal Shortest Distances from {start}:")
            for vertex in sorted(self.vertices):
                if distances[vertex] == float('infinity'):
                    print(f"  {vertex}: No path (∞)")
                else:
                    print(f"  {vertex}: {distances[vertex]:.1f}")
            
            print(f"\nPrevious Vertices (for path reconstruction):")
            for vertex in sorted(self.vertices):
                if previous[vertex] is not None:
                    print(f"  {vertex} ← {previous[vertex]}")
                else:
                    print(f"  {vertex} ← None")
        
        return result
    
    def dijkstra_simple_array(self, start: str) -> DijkstraResult:
        """
        Dijkstra's algorithm implementation using simple array (less efficient).
        
        Educational Purpose:
        - Shows the basic algorithm without priority queue optimization
        - Demonstrates why priority queues are important
        - Easier to understand for beginners
        - Shows the difference in time complexity
        
        Args:
            start: Source vertex for shortest path calculation
            
        Returns:
            DijkstraResult containing distances, previous vertices, and execution details
            
        Time Complexity: O(V²) - must scan all vertices to find minimum
        Space Complexity: O(V) for arrays
        """
        if self.debug:
            print(f"\n{'='*60}")
            print(f"DIJKSTRA'S ALGORITHM (Simple Array Implementation)")
            print(f"Starting from vertex: {start}")
            print(f"{'='*60}")
        
        start_time = time.time()
        
        # Initialize data structures
        distances = {vertex: float('infinity') for vertex in self.vertices}
        previous = {vertex: None for vertex in self.vertices}
        processed = set()
        
        distances[start] = 0
        
        algorithm_steps = []
        vertices_processed = 0
        
        if self.debug:
            print(f"\nInitialization:")
            print(f"  Source vertex: {start}")
            print(f"  Initial distances: {distances}")
        
        # Main algorithm loop
        while len(processed) < len(self.vertices):
            # Find vertex with minimum distance (not yet processed)
            min_distance = float('infinity')
            current_vertex = None
            
            for vertex in self.vertices:
                if vertex not in processed and distances[vertex] < min_distance:
                    min_distance = distances[vertex]
                    current_vertex = vertex
            
            # If no vertex found, remaining vertices are unreachable
            if current_vertex is None:
                break
            
            # Mark vertex as processed
            processed.add(current_vertex)
            vertices_processed += 1
            
            if self.debug:
                print(f"\nStep {vertices_processed}: Processing vertex {current_vertex}")
                print(f"  Distance from source: {min_distance}")
            
            # Relax all edges from current vertex
            edges_relaxed = []
            if current_vertex in self.graph:
                for neighbor, edge_weight in self.graph[current_vertex]:
                    if neighbor not in processed:
                        new_distance = min_distance + edge_weight
                        
                        if new_distance < distances[neighbor]:
                            old_distance = distances[neighbor]
                            distances[neighbor] = new_distance
                            previous[neighbor] = current_vertex
                            
                            edges_relaxed.append({
                                'neighbor': neighbor,
                                'edge_weight': edge_weight,
                                'old_distance': old_distance,
                                'new_distance': new_distance,
                                'improvement': old_distance - new_distance
                            })
                            
                            if self.debug:
                                print(f"    Relaxed edge to {neighbor}: {old_distance} → {new_distance}")
            
            # Record step
            algorithm_steps.append({
                'step': vertices_processed,
                'current_vertex': current_vertex,
                'current_distance': min_distance,
                'edges_relaxed': edges_relaxed,
                'distances': distances.copy()
            })
        
        execution_time = time.time() - start_time
        
        # Determine which vertices have paths from source
        path_found = {}
        for vertex in self.vertices:
            path_found[vertex] = distances[vertex] != float('infinity')
        
        result = DijkstraResult(
            distances=distances,
            previous=previous,
            execution_time=execution_time,
            vertices_processed=vertices_processed,
            total_vertices=len(self.vertices),
            path_found=path_found,
            algorithm_steps=algorithm_steps
        )
        
        if self.debug:
            print(f"\n{'='*60}")
            print("DIJKSTRA'S ALGORITHM COMPLETED (Simple Array)")
            print(f"{'='*60}")
            print(f"Execution Summary:")
            print(f"  Vertices processed: {vertices_processed}/{len(self.vertices)}")
            print(f"  Execution time: {execution_time:.6f} seconds")
            print(f"  Time complexity: O(V²) - less efficient than binary heap")
        
        return result
    
    def reconstruct_path(self, start: str, end: str, previous: Dict[str, Optional[str]]) -> Optional[List[str]]:
        """
        Reconstruct shortest path from start to end using previous vertices.
        
        Educational Purpose:
        - Shows how to trace back from destination to source
        - Demonstrates path reconstruction technique
        - Useful for understanding how shortest paths are stored
        
        Args:
            start: Source vertex
            end: Destination vertex
            previous: Dictionary mapping each vertex to its previous vertex in shortest path
            
        Returns:
            List of vertices forming shortest path, or None if no path exists
            
        Time Complexity: O(V) - worst case path length
        Space Complexity: O(V) - for path storage
        """
        if end not in previous or previous[end] is None and end != start:
            return None
        
        path = []
        current = end
        
        # Trace back from end to start
        while current is not None:
            path.append(current)
            current = previous[current]
        
        # Reverse to get path from start to end
        path.reverse()
        
        if self.debug:
            if path:
                path_str = " → ".join(path)
                print(f"Shortest path from {start} to {end}: {path_str}")
                print(f"Path length: {len(path) - 1} edges")
            else:
                print(f"No path found from {start} to {end}")
        
        return path
    
    def find_shortest_path(self, start: str, end: str, use_binary_heap: bool = True) -> Tuple[Optional[List[str]], float]:
        """
        Find shortest path between two specific vertices.
        
        Args:
            start: Source vertex
            end: Destination vertex
            use_binary_heap: True for efficient implementation, False for simple array
            
        Returns:
            Tuple of (path, distance) where path is list of vertices or None if no path exists
            
        Educational Benefits:
        - Shows complete shortest path solution
        - Demonstrates path reconstruction
        - Provides distance information
        """
        # Run Dijkstra's algorithm
        if use_binary_heap:
            result = self.dijkstra_binary_heap(start)
        else:
            result = self.dijkstra_simple_array(start)
        
        # Reconstruct path
        path = self.reconstruct_path(start, end, result.previous)
        
        # Get distance
        distance = result.distances[end] if end in result.distances else float('infinity')
        
        return path, distance
    
    def compare_implementations(self, start: str) -> None:
        """
        Compare binary heap vs simple array implementations.
        
        Educational Purpose:
        - Shows performance difference between implementations
        - Demonstrates importance of data structure choice
        - Provides timing analysis for different approaches
        
        Args:
            start: Source vertex for comparison
        """
        print(f"\n{'='*70}")
        print("COMPARING DIJKSTRA IMPLEMENTATIONS")
        print(f"{'='*70}")
        
        # Run both implementations
        print("\n1. Binary Heap Implementation:")
        result_heap = self.dijkstra_binary_heap(start)
        
        print("\n2. Simple Array Implementation:")
        result_array = self.dijkstra_simple_array(start)
        
        # Compare results
        print(f"\n{'='*70}")
        print("PERFORMANCE COMPARISON")
        print(f"{'='*70}")
        
        print(f"Binary Heap Implementation:")
        print(f"  Time Complexity: O((V + E) log V)")
        print(f"  Execution Time: {result_heap.execution_time:.6f} seconds")
        print(f"  Vertices Processed: {result_heap.vertices_processed}")
        
        print(f"\nSimple Array Implementation:")
        print(f"  Time Complexity: O(V²)")
        print(f"  Execution Time: {result_array.execution_time:.6f} seconds")
        print(f"  Vertices Processed: {result_array.vertices_processed}")
        
        # Verify results are identical
        distances_match = result_heap.distances == result_array.distances
        print(f"\nResults Verification:")
        print(f"  Distances match: {distances_match}")
        
        if not distances_match:
            print("  WARNING: Results differ between implementations!")
            print("  Binary Heap distances:", result_heap.distances)
            print("  Simple Array distances:", result_array.distances)
        
        # Performance ratio
        if result_array.execution_time > 0:
            speedup = result_array.execution_time / result_heap.execution_time
            print(f"  Speedup (Heap vs Array): {speedup:.2f}x")
    
    def analyze_algorithm_complexity(self) -> None:
        """
        Analyze and explain algorithm complexity.
        
        Educational Purpose:
        - Explains why Dijkstra's algorithm has its time complexity
        - Shows impact of data structure choice
        - Provides complexity analysis for different scenarios
        """
        print(f"\n{'='*60}")
        print("DIJKSTRA'S ALGORITHM COMPLEXITY ANALYSIS")
        print(f"{'='*60}")
        
        V = len(self.vertices)
        E = sum(len(neighbors) for neighbors in self.graph.values())
        
        print(f"Graph Statistics:")
        print(f"  Vertices (V): {V}")
        print(f"  Edges (E): {E}")
        print(f"  Graph Density: {E / (V * (V - 1)):.3f}" if V > 1 else "  Graph Density: N/A")
        
        print(f"\nTime Complexity Analysis:")
        print(f"  Binary Heap Implementation: O((V + E) log V)")
        print(f"    - Each vertex extracted once: V operations")
        print(f"    - Each edge relaxed once: E operations")
        print(f"    - Heap operations: O(log V) each")
        print(f"    - Total: O((V + E) log V)")
        
        print(f"\n  Simple Array Implementation: O(V²)")
        print(f"    - Finding minimum distance: O(V) per vertex")
        print(f"    - V vertices processed: O(V²) total")
        print(f"    - Edge relaxation: O(E) additional")
        print(f"    - Total: O(V² + E)")
        
        print(f"\nSpace Complexity: O(V)")
        print(f"  - Distance array: O(V)")
        print(f"  - Previous vertex array: O(V)")
        print(f"  - Priority queue: O(V)")
        
        print(f"\nWhen to Use Each Implementation:")
        print(f"  Binary Heap: Best for sparse graphs (E << V²)")
        print(f"  Simple Array: Acceptable for dense graphs (E ≈ V²)")
        
        # Estimate performance for this graph
        heap_operations = (V + E) * (1 if V <= 1 else V.bit_length())  # log V approximation
        array_operations = V * V + E
        
        print(f"\nEstimated Operations for This Graph:")
        print(f"  Binary Heap: ~{heap_operations:,} operations")
        print(f"  Simple Array: ~{array_operations:,} operations")
        
        if array_operations > 0:
            ratio = array_operations / heap_operations
            print(f"  Array is ~{ratio:.1f}x more operations than heap")


def demonstrate_dijkstra_algorithm():
    """
    Comprehensive demonstration of Dijkstra's algorithm.
    
    Educational Goals:
    1. Show Dijkstra's algorithm in action with real examples
    2. Demonstrate different implementations and their trade-offs
    3. Provide hands-on experience with shortest path algorithms
    4. Show real-world applications and use cases
    5. Teach debugging and analysis techniques
    """
    
    print("=" * 80)
    print("COMPREHENSIVE DIJKSTRA'S ALGORITHM DEMONSTRATION")
    print("=" * 80)
    
    # Example 1: Simple graph for understanding
    print("\n1. Simple Graph Example")
    print("-" * 30)
    
    simple_graph = {
        'A': [('B', 4), ('C', 2)],
        'B': [('C', 1), ('D', 5)],
        'C': [('D', 8), ('E', 10)],
        'D': [('E', 2)],
        'E': []
    }
    
    print("Graph Structure:")
    print("    A --4-- B --5-- D")
    print("    |       |       |")
    print("    2       1       2")
    print("    |       |       |")
    print("    C --8-- D --10-- E")
    
    dijkstra_simple = DijkstraAlgorithm(simple_graph, debug=True)
    
    # Find shortest paths from A
    result = dijkstra_simple.dijkstra_binary_heap('A')
    
    # Find specific path
    path, distance = dijkstra_simple.find_shortest_path('A', 'E')
    
    # Example 2: GPS navigation simulation
    print("\n2. GPS Navigation Simulation")
    print("-" * 35)
    
    city_graph = {
        'Home': [('Work', 15), ('Gym', 8), ('Store', 12)],
        'Work': [('Home', 15), ('Gym', 6), ('Airport', 25)],
        'Gym': [('Home', 8), ('Work', 6), ('Store', 5)],
        'Store': [('Home', 12), ('Gym', 5), ('Airport', 20)],
        'Airport': [('Work', 25), ('Store', 20)]
    }
    
    print("City Navigation Graph:")
    print("    Home --15-- Work --25-- Airport")
    print("    |      |              |")
    print("    8      6              20")
    print("    |      |              |")
    print("    Gym --5-- Store ------+")
    
    gps = DijkstraAlgorithm(city_graph, debug=True)
    
    # Find shortest route from Home to Airport
    route, travel_time = gps.find_shortest_path('Home', 'Airport')
    
    # Example 3: Network routing simulation
    print("\n3. Network Routing Simulation")
    print("-" * 35)
    
    network_graph = {
        'Router1': [('Router2', 3), ('Router3', 7)],
        'Router2': [('Router1', 3), ('Router4', 4), ('Router5', 2)],
        'Router3': [('Router1', 7), ('Router4', 1), ('Router6', 5)],
        'Router4': [('Router2', 4), ('Router3', 1), ('Router7', 3)],
        'Router5': [('Router2', 2), ('Router7', 6)],
        'Router6': [('Router3', 5), ('Router7', 2)],
        'Router7': [('Router4', 3), ('Router5', 6), ('Router6', 2)]
    }
    
    print("Network Topology:")
    print("    R1 --3-- R2 --4-- R4 --3-- R7")
    print("    |         |         |         |")
    print("    7         2         1         6")
    print("    |         |         |         |")
    print("    R3 --5-- R6 --2-- R7 --6-- R5")
    
    network = DijkstraAlgorithm(network_graph, debug=True)
    
    # Find shortest path between routers
    network_path, latency = network.find_shortest_path('Router1', 'Router7')
    
    # Example 4: Algorithm comparison
    print("\n4. Implementation Comparison")
    print("-" * 35)
    
    dijkstra_simple.compare_implementations('A')
    
    # Example 5: Complexity analysis
    print("\n5. Complexity Analysis")
    print("-" * 25)
    
    dijkstra_simple.analyze_algorithm_complexity()
    
    # Example 6: Real-world applications summary
    print("\n6. Real-World Applications")
    print("-" * 30)
    
    applications = [
        "GPS Navigation Systems - Finding shortest driving routes",
        "Network Routing Protocols - Internet packet routing",
        "Social Network Analysis - Influence propagation",
        "Game AI Pathfinding - Character movement optimization",
        "Resource Allocation - Delivery route optimization",
        "Flight Planning - Airline route optimization",
        "Telecommunications - Network design and optimization",
        "Robotics - Path planning for autonomous vehicles"
    ]
    
    print("Dijkstra's algorithm is used in:")
    for i, app in enumerate(applications, 1):
        print(f"  {i}. {app}")
    
    # Example 7: Common pitfalls and limitations
    print("\n7. Common Pitfalls and Limitations")
    print("-" * 40)
    
    print("Important Limitations:")
    print("  ❌ Negative edge weights: Algorithm fails with negative weights")
    print("  ❌ Negative cycles: Cannot detect or handle negative cycles")
    print("  ❌ All-pairs shortest paths: Inefficient for finding all pairs")
    
    print("\nCommon Mistakes:")
    print("  ⚠️  Using wrong data structure (array vs heap)")
    print("  ⚠️  Not handling unreachable vertices")
    print("  ⚠️  Incorrect edge relaxation logic")
    print("  ⚠️  Forgetting to update priority queue")
    
    print("\nBest Practices:")
    print("  ✅ Use binary heap for efficiency")
    print("  ✅ Validate input graph (no negative weights)")
    print("  ✅ Handle edge cases (disconnected graphs)")
    print("  ✅ Test with various graph sizes")
    
    print("\n" + "=" * 80)
    print("DIJKSTRA'S ALGORITHM DEMONSTRATION COMPLETED")
    print("=" * 80)


if __name__ == "__main__":
    demonstrate_dijkstra_algorithm()
