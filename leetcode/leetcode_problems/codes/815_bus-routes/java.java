import java.util.*;

class Solution {
    public int numBusesToDestination(int[][] routes, int source, int target) {
        if (source == target) {
            return 0;
        }
        
        Map<Integer, List<Integer>> stopToRoutes = new HashMap<>();
        for (int i = 0; i < routes.length; i++) {
            for (int stop : routes[i]) {
                stopToRoutes.computeIfAbsent(stop, k -> new ArrayList<>()).add(i);
            }
        }
        
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(source);
        Set<Integer> visited = new HashSet<>();
        int buses = 0;
        
        while (!queue.isEmpty()) {
            buses++;
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int stop = queue.poll();
                for (int routeIdx : stopToRoutes.getOrDefault(stop, Collections.emptyList())) {
                    if (visited.contains(routeIdx)) {
                        continue;
                    }
                    visited.add(routeIdx);
                    for (int nextStop : routes[routeIdx]) {
                        if (nextStop == target) {
                            return buses;
                        }
                        queue.offer(nextStop);
                    }
                }
            }
        }
        
        return -1;
    }
}
