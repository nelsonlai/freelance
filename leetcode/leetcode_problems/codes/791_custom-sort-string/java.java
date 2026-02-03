import java.util.*;

class Solution {
    public String customSortString(String order, String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        StringBuilder result = new StringBuilder();
        for (char c : order.toCharArray()) {
            int freq = count.getOrDefault(c, 0);
            result.append(String.valueOf(c).repeat(freq));
            count.put(c, 0);
        }
        
        for (Map.Entry<Character, Integer> entry : count.entrySet()) {
            result.append(String.valueOf(entry.getKey()).repeat(entry.getValue()));
        }
        
        return result.toString();
    }
}
