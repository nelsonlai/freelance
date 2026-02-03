/**
 * Problem: Design Phone Directory
 * Difficulty: Medium
 * Tags: array, hash, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class PhoneDirectory {
    private Set<Integer> available;
    private Set<Integer> used;

    public PhoneDirectory(int maxNumbers) {
        available = new HashSet<>();
        used = new HashSet<>();
        for (int i = 0; i < maxNumbers; i++) {
            available.add(i);
        }
    }
    
    public int get() {
        if (available.isEmpty()) {
            return -1;
        }
        int number = available.iterator().next();
        available.remove(number);
        used.add(number);
        return number;
    }
    
    public boolean check(int number) {
        return available.contains(number);
    }
    
    public void release(int number) {
        if (used.contains(number)) {
            used.remove(number);
            available.add(number);
        }
    }
}

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * boolean param_2 = obj.check(number);
 * obj.release(number);
 */