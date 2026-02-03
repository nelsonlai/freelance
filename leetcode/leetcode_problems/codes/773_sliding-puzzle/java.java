import java.util.*;

class Solution {
    public int slidingPuzzle(int[][] board) {
        String target = "123450";
        StringBuilder sb = new StringBuilder();
        for (int[] row : board) {
            for (int num : row) {
                sb.append(num);
            }
        }
        String start = sb.toString();
        
        int[][] neighbors = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
        
        Queue<String[]> queue = new LinkedList<>();
        queue.offer(new String[]{start, "0"});
        Set<String> visited = new HashSet<>();
        visited.add(start);
        
        while (!queue.isEmpty()) {
            String[] curr = queue.poll();
            String state = curr[0];
            int moves = Integer.parseInt(curr[1]);
            
            if (state.equals(target)) {
                return moves;
            }
            
            int zeroIdx = state.indexOf('0');
            for (int neighbor : neighbors[zeroIdx]) {
                char[] chars = state.toCharArray();
                char temp = chars[zeroIdx];
                chars[zeroIdx] = chars[neighbor];
                chars[neighbor] = temp;
                String newState = new String(chars);
                if (!visited.contains(newState)) {
                    visited.add(newState);
                    queue.offer(new String[]{newState, String.valueOf(moves + 1)});
                }
            }
        }
        
        return -1;
    }
}
