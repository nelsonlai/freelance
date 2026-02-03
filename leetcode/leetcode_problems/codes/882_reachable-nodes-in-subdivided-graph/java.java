import java.util.*;

class Solution {
    public int reachableNodes(int[][] edges, int maxMoves, int n) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2] + 1});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2] + 1});
        }
        
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        heap.offer(new int[]{0, 0});
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int d = curr[0], node = curr[1];
            if (d > dist[node]) continue;
            for (int[] edge : graph.get(node)) {
                int neighbor = edge[0], weight = edge[1];
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    heap.offer(new int[]{dist[neighbor], neighbor});
                }
            }
        }
        
        int result = 0;
        for (int d : dist) {
            if (d <= maxMoves) result++;
        }
        
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            int a = Math.max(0, maxMoves - dist[u]);
            int b = Math.max(0, maxMoves - dist[v]);
            result += Math.min(a + b, w);
        }
        
        return result;
    }
}
