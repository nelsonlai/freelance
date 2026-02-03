/**
 * Problem: Two Sum III - Data structure design
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class TwoSum {
    private Map<Integer, Integer> numbers;

    public TwoSum() {
        numbers = new HashMap<>();
    }
    
    public void add(int number) {
        numbers.put(number, numbers.getOrDefault(number, 0) + 1);
    }
    
    public boolean find(int value) {
        for (int num : numbers.keySet()) {
            int complement = value - num;
            if (numbers.containsKey(complement)) {
                if (complement != num || numbers.get(num) > 1) {
                    return true;
                }
            }
        }
        return false;
    }
}

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * boolean param_2 = obj.find(value);
 */