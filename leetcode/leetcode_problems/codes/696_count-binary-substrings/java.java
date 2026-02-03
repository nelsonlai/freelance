/**
 * Problem: Count Binary Substrings
 * Difficulty: Easy
 * Tags: array, string, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int countBinarySubstrings(String s) {
        List<Integer> groups = new ArrayList<>();
        int count = 1;
        
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) != s.charAt(i - 1)) {
                groups.add(count);
                count = 1;
            } else {
                count++;
            }
        }
        groups.add(count);
        
        int result = 0;
        for (int i = 1; i < groups.size(); i++) {
            result += Math.min(groups.get(i - 1), groups.get(i));
        }
        
        return result;
    }
}