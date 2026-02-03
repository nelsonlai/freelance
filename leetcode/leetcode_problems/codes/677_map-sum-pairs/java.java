/**
 * Problem: Map Sum Pairs
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class MapSum {
    private Map<String, Integer> map;
    private Map<String, Integer> prefixMap;

    public MapSum() {
        map = new HashMap<>();
        prefixMap = new HashMap<>();
    }
    
    public void insert(String key, int val) {
        int delta = val - map.getOrDefault(key, 0);
        map.put(key, val);
        
        for (int i = 1; i <= key.length(); i++) {
            String prefix = key.substring(0, i);
            prefixMap.put(prefix, prefixMap.getOrDefault(prefix, 0) + delta);
        }
    }
    
    public int sum(String prefix) {
        return prefixMap.getOrDefault(prefix, 0);
    }
}

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */