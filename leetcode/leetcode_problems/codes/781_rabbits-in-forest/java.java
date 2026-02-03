import java.util.*;

class Solution {
    public int numRabbits(int[] answers) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int ans : answers) {
            count.put(ans, count.getOrDefault(ans, 0) + 1);
        }
        
        int result = 0;
        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            int answer = entry.getKey();
            int freq = entry.getValue();
            result += (freq + answer) / (answer + 1) * (answer + 1);
        }
        return result;
    }
}
