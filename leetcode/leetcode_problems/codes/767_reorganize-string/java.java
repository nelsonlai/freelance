import java.util.*;

class Solution {
    public String reorganizeString(String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        for (Map.Entry<Character, Integer> entry : count.entrySet()) {
            heap.offer(new int[]{entry.getValue(), entry.getKey()});
        }
        
        StringBuilder result = new StringBuilder();
        int[] prev = null;
        
        while (!heap.isEmpty() || prev != null) {
            if (heap.isEmpty() && prev != null) {
                return "";
            }
            
            int[] curr = heap.poll();
            result.append((char)curr[1]);
            curr[0]--;
            
            if (prev != null) {
                heap.offer(prev);
                prev = null;
            }
            
            if (curr[0] > 0) {
                prev = curr;
            }
        }
        
        return result.toString();
    }
}
