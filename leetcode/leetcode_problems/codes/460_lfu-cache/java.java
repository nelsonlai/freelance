/**
 * Problem: LFU Cache
 * Difficulty: Hard
 * Tags: hash, linked_list
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class LFUCache {
    private int capacity;
    private int minFreq;
    private Map<Integer, Integer> keyToFreq;
    private Map<Integer, LinkedHashMap<Integer, Integer>> freqToKeys;

    public LFUCache(int capacity) {
        this.capacity = capacity;
        this.minFreq = 0;
        this.keyToFreq = new HashMap<>();
        this.freqToKeys = new HashMap<>();
    }
    
    public int get(int key) {
        if (!keyToFreq.containsKey(key)) {
            return -1;
        }
        
        int freq = keyToFreq.get(key);
        LinkedHashMap<Integer, Integer> keys = freqToKeys.get(freq);
        int value = keys.get(key);
        
        keys.remove(key);
        if (keys.isEmpty() && freq == minFreq) {
            minFreq++;
        }
        
        keyToFreq.put(key, freq + 1);
        freqToKeys.putIfAbsent(freq + 1, new LinkedHashMap<>());
        freqToKeys.get(freq + 1).put(key, value);
        
        return value;
    }
    
    public void put(int key, int value) {
        if (capacity == 0) {
            return;
        }
        
        if (keyToFreq.containsKey(key)) {
            get(key);
            int freq = keyToFreq.get(key);
            freqToKeys.get(freq).put(key, value);
            return;
        }
        
        if (keyToFreq.size() >= capacity) {
            LinkedHashMap<Integer, Integer> keys = freqToKeys.get(minFreq);
            int lfuKey = keys.keySet().iterator().next();
            keys.remove(lfuKey);
            keyToFreq.remove(lfuKey);
        }
        
        keyToFreq.put(key, 1);
        freqToKeys.putIfAbsent(1, new LinkedHashMap<>());
        freqToKeys.get(1).put(key, value);
        minFreq = 1;
    }
}

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */