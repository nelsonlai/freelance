/**
 * Problem: First Unique Number
 * Difficulty: Medium
 * Tags: array, hash, queue
 * 
 * Approach: Use LinkedHashMap to maintain insertion order, track counts
 * Time Complexity: O(1) for showFirstUnique, O(1) for add
 * Space Complexity: O(n) for counts and map
 */

import java.util.*;

class FirstUnique {
    private Map<Integer, Integer> count;
    private LinkedHashSet<Integer> unique;

    public FirstUnique(int[] nums) {
        count = new HashMap<>();
        unique = new LinkedHashSet<>();
        for (int num : nums) {
            add(num);
        }
    }
    
    public int showFirstUnique() {
        if (!unique.isEmpty()) {
            return unique.iterator().next();
        }
        return -1;
    }
    
    public void add(int value) {
        if (!count.containsKey(value)) {
            count.put(value, 1);
            unique.add(value);
        } else {
            count.put(value, count.get(value) + 1);
            unique.remove(value);
        }
    }
}

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique obj = new FirstUnique(nums);
 * int param_1 = obj.showFirstUnique();
 * obj.add(value);
 */