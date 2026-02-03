/**
 * Problem: All O`one Data Structure
 * Difficulty: Hard
 * Tags: string, hash, linked_list
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class AllOne {
    private Map<String, Integer> count;
    private int minCount;
    private int maxCount;

    public AllOne() {
        count = new HashMap<>();
        minCount = Integer.MAX_VALUE;
        maxCount = 0;
    }
    
    public void inc(String key) {
        count.put(key, count.getOrDefault(key, 0) + 1);
        int cnt = count.get(key);
        maxCount = Math.max(maxCount, cnt);
        if (cnt == 1) {
            minCount = Math.min(minCount, 1);
        } else {
            if (minCount == cnt - 1) {
                minCount = count.values().stream().filter(v -> v > 0).mapToInt(v -> v).min().orElse(Integer.MAX_VALUE);
            }
        }
    }
    
    public void dec(String key) {
        if (count.containsKey(key)) {
            count.put(key, count.get(key) - 1);
            if (count.get(key) == 0) {
                count.remove(key);
                if (count.isEmpty()) {
                    minCount = Integer.MAX_VALUE;
                    maxCount = 0;
                } else {
                    minCount = Collections.min(count.values());
                    maxCount = Collections.max(count.values());
                }
            } else {
                minCount = Collections.min(count.values());
                if (maxCount == count.get(key) + 1) {
                    maxCount = Collections.max(count.values());
                }
            }
        }
    }
    
    public String getMaxKey() {
        if (count.isEmpty()) {
            return "";
        }
        for (Map.Entry<String, Integer> entry : count.entrySet()) {
            if (entry.getValue() == maxCount) {
                return entry.getKey();
            }
        }
        return "";
    }
    
    public String getMinKey() {
        if (count.isEmpty()) {
            return "";
        }
        for (Map.Entry<String, Integer> entry : count.entrySet()) {
            if (entry.getValue() == minCount) {
                return entry.getKey();
            }
        }
        return "";
    }
}

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * String param_3 = obj.getMaxKey();
 * String param_4 = obj.getMinKey();
 */