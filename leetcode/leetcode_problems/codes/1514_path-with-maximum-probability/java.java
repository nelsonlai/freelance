/**
 * Problem: Path with Maximum Probability
 * Difficulty: Medium
 * Tags: array, graph, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public double maxProbability(int n, int[][] edges, double[] succProb, int start_node, int end_node) {
        List<List<double[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];
            graph.get(u).add(new double[]{v, prob});
            graph.get(v).add(new double[]{u, prob});
        }
        
        double[] maxProb = new double[n];
        maxProb[start_node] = 1.0;
        
        PriorityQueue<double[]> heap = new PriorityQueue<>((a, b) -> Double.compare(b[1], a[1]));
        heap.offer(new double[]{start_node, 1.0});
        
        while (!heap.isEmpty()) {
            double[] current = heap.poll();
            int node = (int) current[0];
            double prob = current[1];
            
            if (node == end_node) {
                return prob;
            }
            
            if (prob < maxProb[node]) {
                continue;
            }
            
            for (double[] neighbor : graph.get(node)) {
                int next = (int) neighbor[0];
                double edgeProb = neighbor[1];
                double newProb = prob * edgeProb;
                
                if (newProb > maxProb[next]) {
                    maxProb[next] = newProb;
                    heap.offer(new double[]{next, newProb});
                }
            }
        }
        
        return 0.0;
    }
}