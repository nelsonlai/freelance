import java.util.*;

class Solution {
    public int rectangleArea(int[][] rectangles) {
        int MOD = 1000000007;
        List<int[]> events = new ArrayList<>();
        for (int[] rect : rectangles) {
            events.add(new int[]{rect[1], 1, rect[0], rect[2]});
            events.add(new int[]{rect[3], -1, rect[0], rect[2]});
        }
        events.sort((a, b) -> a[0] - b[0]);
        
        List<int[]> active = new ArrayList<>();
        long result = 0;
        int curY = events.get(0)[0];
        
        for (int[] event : events) {
            int y = event[0], typ = event[1], x1 = event[2], x2 = event[3];
            result += query(active) * (y - curY);
            curY = y;
            
            if (typ == 1) {
                active.add(new int[]{x1, x2});
                active.sort((a, b) -> a[0] - b[0]);
            } else {
                for (int i = 0; i < active.size(); i++) {
                    if (active.get(i)[0] == x1 && active.get(i)[1] == x2) {
                        active.remove(i);
                        break;
                    }
                }
            }
        }
        
        return (int)(result % MOD);
    }
    
    private long query(List<int[]> active) {
        long result = 0;
        int cur = -1;
        for (int[] interval : active) {
            cur = Math.max(cur, interval[0]);
            result += Math.max(0, interval[1] - cur);
            cur = Math.max(cur, interval[1]);
        }
        return result;
    }
}
