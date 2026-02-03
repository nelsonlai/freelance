/**
 * Problem: Insert Delete GetRandom O(1) - Duplicates allowed
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class RandomizedCollection {
    private List<Integer> nums;
    private Map<Integer, Set<Integer>> valToIndices;

    public RandomizedCollection() {
        nums = new ArrayList<>();
        valToIndices = new HashMap<>();
    }
    
    public boolean insert(int val) {
        valToIndices.putIfAbsent(val, new HashSet<>());
        valToIndices.get(val).add(nums.size());
        nums.add(val);
        return valToIndices.get(val).size() == 1;
    }
    
    public boolean remove(int val) {
        if (!valToIndices.containsKey(val) || valToIndices.get(val).isEmpty()) {
            return false;
        }
        
        int idx = valToIndices.get(val).iterator().next();
        valToIndices.get(val).remove(idx);
        int lastVal = nums.get(nums.size() - 1);
        
        nums.set(idx, lastVal);
        valToIndices.get(lastVal).add(idx);
        valToIndices.get(lastVal).remove(nums.size() - 1);
        
        nums.remove(nums.size() - 1);
        return true;
    }
    
    public int getRandom() {
        return nums.get((int)(Math.random() * nums.size()));
    }
}

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * boolean param_1 = obj.insert(val);
 * boolean param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */