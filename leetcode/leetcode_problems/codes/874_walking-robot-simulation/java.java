import java.util.*;

class Solution {
    public int robotSim(int[] commands, int[][] obstacles) {
        Set<String> obstaclesSet = new HashSet<>();
        for (int[] ob : obstacles) {
            obstaclesSet.add(ob[0] + "," + ob[1]);
        }
        
        int x = 0, y = 0;
        int dx = 0, dy = 1;
        int result = 0;
        
        for (int cmd : commands) {
            if (cmd == -2) {
                int temp = dx;
                dx = -dy;
                dy = temp;
            } else if (cmd == -1) {
                int temp = dx;
                dx = dy;
                dy = -temp;
            } else {
                for (int i = 0; i < cmd; i++) {
                    String next = (x + dx) + "," + (y + dy);
                    if (!obstaclesSet.contains(next)) {
                        x += dx;
                        y += dy;
                        result = Math.max(result, x * x + y * y);
                    } else {
                        break;
                    }
                }
            }
        }
        return result;
    }
}
