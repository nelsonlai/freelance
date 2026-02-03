# Graph Algorithms Python Implementation

This repository contains comprehensive Python implementations of graph algorithms with detailed demonstrations and educational materials.

## Files Overview

### Core Implementation Files

1. **`graph_class.py`** - Core Graph class with adjacency list representation
   - Supports both directed and undirected graphs
   - Weighted and unweighted edges
   - Various utility methods for graph operations

2. **`graph_traversal.py`** - Graph traversal algorithms
   - Breadth-First Search (BFS)
   - Depth-First Search (DFS)
   - Path finding and cycle detection
   - Connected components analysis

3. **`shortest_path.py`** - Shortest path algorithms
   - Dijkstra's algorithm (non-negative weights)
   - Bellman-Ford algorithm (handles negative weights)
   - Floyd-Warshall algorithm (all-pairs shortest paths)

4. **`minimum_spanning_tree.py`** - MST algorithms
   - Kruskal's algorithm with Union-Find
   - Prim's algorithm
   - Algorithm comparison and visualization

5. **`topological_sort.py`** - Topological sorting
   - Kahn's algorithm
   - DFS-based algorithm
   - Cycle detection and all possible orderings

6. **`strongly_connected_components.py`** - SCC algorithms
   - Kosaraju's algorithm
   - Tarjan's algorithm
   - Condensation graph creation

7. **`comprehensive_demo.py`** - Interactive demonstration program
   - Menu-driven interface
   - All algorithm demonstrations
   - Interactive graph builder

### Documentation

8. **`detailed_graph_algorithms_teaching_guide.md`** - Comprehensive teaching material
   - Detailed explanations of all concepts
   - Algorithm pseudocode and implementations
   - Real-world applications and examples
   - Assessment tools and practice problems

## Quick Start

### Running Individual Algorithms

```bash
# Run the comprehensive demo
python comprehensive_demo.py

# Run individual algorithm demonstrations
python graph_class.py
python graph_traversal.py
python shortest_path.py
python minimum_spanning_tree.py
python topological_sort.py
python strongly_connected_components.py
```

### Basic Usage Example

```python
from graph_class import Graph
from graph_traversal import GraphTraversal
from shortest_path import ShortestPath

# Create a graph
graph = Graph(directed=False)
graph.add_edge('A', 'B', 3)
graph.add_edge('A', 'C', 1)
graph.add_edge('B', 'D', 2)

# Perform BFS
traversal = GraphTraversal(graph)
bfs_result = traversal.bfs('A')
print(f"BFS order: {bfs_result['traversal_order']}")

# Find shortest paths
sp = ShortestPath(graph)
distances, previous = sp.dijkstra('A')
print(f"Shortest distances: {distances}")
```

## Features

### Graph Class Features
- **Flexible representation**: Adjacency list with optional weights
- **Graph types**: Directed and undirected graphs
- **Utility methods**: Degree calculation, connectivity checking, edge operations
- **Visualization**: ASCII art representation and adjacency matrix printing

### Algorithm Implementations
- **Complete implementations** with step-by-step execution tracking
- **Detailed comments** explaining each step
- **Error handling** for invalid inputs and edge cases
- **Performance analysis** with complexity information

### Educational Features
- **Interactive demonstrations** with visual output
- **Real-world examples** (course prerequisites, social networks, etc.)
- **Algorithm comparisons** showing trade-offs
- **Comprehensive documentation** with teaching materials

## Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity | Best For |
|-----------|----------------|------------------|----------|
| BFS | O(V + E) | O(V) | Shortest path (unweighted) |
| DFS | O(V + E) | O(V) | Cycle detection, topological sort |
| Dijkstra | O((V + E) log V) | O(V) | Non-negative weights |
| Bellman-Ford | O(VE) | O(V) | Negative weights, cycle detection |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs shortest paths |
| Kruskal MST | O(E log E) | O(V) | Sparse graphs |
| Prim MST | O(E log V) | O(V) | Dense graphs |
| Topological Sort | O(V + E) | O(V) | DAG ordering |
| Kosaraju SCC | O(V + E) | O(V) | Strongly connected components |
| Tarjan SCC | O(V + E) | O(V) | Strongly connected components |

## Real-World Applications

### Graph Traversal
- **Social networks**: Friend recommendations, influence analysis
- **Web crawling**: Page discovery and indexing
- **Maze solving**: Path finding in games and robotics

### Shortest Path
- **Navigation systems**: GPS routing, flight paths
- **Network routing**: Internet packet routing
- **Resource allocation**: Optimal distribution problems

### Minimum Spanning Tree
- **Network design**: Minimum cost network connections
- **Clustering**: Data grouping and analysis
- **Approximation algorithms**: Traveling salesman problem

### Topological Sorting
- **Build systems**: Dependency resolution
- **Course scheduling**: Prerequisite ordering
- **Task scheduling**: Workflow optimization

### Strongly Connected Components
- **Web analysis**: Page ranking and clustering
- **Social networks**: Community detection
- **Compiler design**: Control flow analysis

## Educational Use

This implementation is designed for:
- **Computer Science students** learning graph algorithms
- **Educators** teaching data structures and algorithms
- **Software developers** implementing graph-based solutions
- **Algorithm researchers** comparing implementations

### Learning Path
1. Start with `graph_class.py` to understand graph representation
2. Explore `graph_traversal.py` for basic algorithms
3. Study `shortest_path.py` for optimization problems
4. Learn `minimum_spanning_tree.py` for connectivity problems
5. Understand `topological_sort.py` for ordering problems
6. Master `strongly_connected_components.py` for complex analysis
7. Use `comprehensive_demo.py` for interactive learning

## Requirements

- Python 3.7+
- No external dependencies (uses only standard library)

## Contributing

This is an educational implementation. Feel free to:
- Add more algorithms
- Improve documentation
- Fix bugs or optimize code
- Add more examples and use cases

## License

This project is for educational purposes. Feel free to use and modify for learning and teaching.

---

**Note**: This implementation prioritizes clarity and educational value over performance optimization. For production use, consider using specialized graph libraries like NetworkX or igraph.
