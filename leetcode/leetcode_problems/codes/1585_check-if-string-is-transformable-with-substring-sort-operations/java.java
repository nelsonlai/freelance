/**
 * Problem: Check If String Is Transformable With Substring Sort Operations
 * Difficulty: Hard
 * Tags: string, tree, greedy, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public boolean isTransformable(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        List<Queue<Integer>> positions = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            positions.add(new LinkedList<>());
        }
        
        for (int i = 0; i < s.length(); i++) {
            positions.get(s.charAt(i) - '0').offer(i);
        }
        
        for (char c : t.toCharArray()) {
            int digit = c - '0';
            if (positions.get(digit).isEmpty()) {
                return false;
            }
            
            int pos = positions.get(digit).peek();
            for (int smaller = 0; smaller < digit; smaller++) {
                if (!positions.get(smaller).isEmpty() && positions.get(smaller).peek() < pos) {
                    return false;
                }
            }
            
            positions.get(digit).poll();
        }
        
        return true;
    }
}