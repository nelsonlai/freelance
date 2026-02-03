/**
 * Problem: The k-th Lexicographical String of All Happy Strings of Length n
 * Difficulty: Medium
 * Tags: string, graph, sort
 * 
 * Approach: Generate happy strings in lexicographical order, return k-th
 * Time Complexity: O(n * 3^n) in worst case
 * Space Complexity: O(n) for recursion
 */

class Solution {
    private String result = "";
    private int count = 0;
    
    public String getHappyString(int n, int k) {
        backtrack(new StringBuilder(), n, k);
        return result;
    }
    
    private void backtrack(StringBuilder current, int n, int k) {
        if (current.length() == n) {
            count++;
            if (count == k) {
                result = current.toString();
            }
            return;
        }
        
        for (char c : new char[]{'a', 'b', 'c'}) {
            if (current.length() == 0 || current.charAt(current.length() - 1) != c) {
                current.append(c);
                backtrack(current, n, k);
                current.deleteCharAt(current.length() - 1);
                if (!result.isEmpty()) {
                    return;
                }
            }
        }
    }
}