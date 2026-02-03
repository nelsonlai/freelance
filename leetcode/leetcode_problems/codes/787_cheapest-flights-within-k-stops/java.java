import java.util.*;

class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        Map<Integer, List<int[]>> graph = new HashMap<>();
        for (int[] flight : flights) {
            graph.computeIfAbsent(flight[0], x -> new ArrayList<>()).add(new int[]{flight[1], flight[2]});
        }
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        heap.offer(new int[]{0, src, k + 1});
        Map<Integer, Integer> visited = new HashMap<>();
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int cost = curr[0], node = curr[1], stops = curr[2];
            
            if (node == dst) {
                return cost;
            }
            
            if (stops > 0) {
                for (int[] edge : graph.getOrDefault(node, Collections.emptyList())) {
                    int neighbor = edge[0], weight = edge[1];
                    int newCost = cost + weight;
                    if (!visited.containsKey(neighbor) || visited.get(neighbor) < stops - 1) {
                        visited.put(neighbor, stops - 1);
                        heap.offer(new int[]{newCost, neighbor, stops - 1});
                    }
                }
            }
        }
        
        return -1;
    }
}
