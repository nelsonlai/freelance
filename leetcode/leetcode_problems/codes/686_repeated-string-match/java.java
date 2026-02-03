/**
 * Problem: Repeated String Match
 * Difficulty: Medium
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int repeatedStringMatch(String a, String b) {
        if (b.isEmpty()) {
            return 0;
        }
        
        int count = (b.length() + a.length() - 1) / a.length();
        StringBuilder repeated = new StringBuilder();
        for (int i = 0; i < count; i++) {
            repeated.append(a);
        }
        
        if (repeated.toString().contains(b)) {
            return count;
        }
        
        repeated.append(a);
        if (repeated.toString().contains(b)) {
            return count + 1;
        }
        
        return -1;
    }
}