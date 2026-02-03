import java.util.*;

class Solution {
    private Set<Integer> visited;
    private List<List<Integer>> rooms;
    
    public boolean canVisitAllRooms(List<List<Integer>> rooms) {
        this.rooms = rooms;
        this.visited = new HashSet<>();
        dfs(0);
        return visited.size() == rooms.size();
    }
    
    private void dfs(int room) {
        if (visited.contains(room)) {
            return;
        }
        visited.add(room);
        for (int key : rooms.get(room)) {
            dfs(key);
        }
    }
}
