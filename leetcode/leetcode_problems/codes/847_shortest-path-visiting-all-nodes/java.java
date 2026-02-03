import java.util.*;

class Solution {
    public int shortestPathLength(int[][] graph) {
        int n = graph.length;
        int target = (1 << n) - 1;
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        
        for (int i = 0; i < n; i++) {
            queue.offer(new int[]{i, 1 << i});
            visited.add(i + "," + (1 << i));
        }
        
        int steps = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] curr = queue.poll();
                int node = curr[0], state = curr[1];
                if (state == target) {
                    return steps;
                }
                for (int neighbor : graph[node]) {
                    int newState = state | (1 << neighbor);
                    String key = neighbor + "," + newState;
                    if (!visited.contains(key)) {
                        visited.add(key);
                        queue.offer(new int[]{neighbor, newState});
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}
