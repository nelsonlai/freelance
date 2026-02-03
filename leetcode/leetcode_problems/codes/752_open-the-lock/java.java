import java.util.*;

class Solution {
    public int openLock(String[] deadends, String target) {
        Set<String> dead = new HashSet<>(Arrays.asList(deadends));
        if (dead.contains("0000")) {
            return -1;
        }
        
        Queue<String[]> queue = new LinkedList<>();
        queue.offer(new String[]{"0000", "0"});
        Set<String> visited = new HashSet<>();
        visited.add("0000");
        
        while (!queue.isEmpty()) {
            String[] curr = queue.poll();
            String state = curr[0];
            int moves = Integer.parseInt(curr[1]);
            
            if (state.equals(target)) {
                return moves;
            }
            
            for (int i = 0; i < 4; i++) {
                for (int d = -1; d <= 1; d += 2) {
                    char[] chars = state.toCharArray();
                    chars[i] = (char)(((chars[i] - '0' + d + 10) % 10) + '0');
                    String newState = new String(chars);
                    if (!visited.contains(newState) && !dead.contains(newState)) {
                        visited.add(newState);
                        queue.offer(new String[]{newState, String.valueOf(moves + 1)});
                    }
                }
            }
        }
        
        return -1;
    }
}
