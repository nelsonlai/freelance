/**
 * Problem: Insert Delete GetRandom O(1)
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class RandomizedSet {
    private List<Integer> nums;
    private Map<Integer, Integer> valToIdx;

    public RandomizedSet() {
        nums = new ArrayList<>();
        valToIdx = new HashMap<>();
    }
    
    public boolean insert(int val) {
        if (valToIdx.containsKey(val)) {
            return false;
        }
        valToIdx.put(val, nums.size());
        nums.add(val);
        return true;
    }
    
    public boolean remove(int val) {
        if (!valToIdx.containsKey(val)) {
            return false;
        }
        
        int idx = valToIdx.get(val);
        int lastVal = nums.get(nums.size() - 1);
        nums.set(idx, lastVal);
        valToIdx.put(lastVal, idx);
        
        nums.remove(nums.size() - 1);
        valToIdx.remove(val);
        return true;
    }
    
    public int getRandom() {
        return nums.get((int)(Math.random() * nums.size()));
    }
}

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * boolean param_1 = obj.insert(val);
 * boolean param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */