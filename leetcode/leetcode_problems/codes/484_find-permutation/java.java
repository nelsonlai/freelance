/**
 * Problem: Find Permutation
 * Difficulty: Medium
 * Tags: array, string, graph, greedy, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] findPermutation(String s) {
        int n = s.length() + 1;
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = i + 1;
        }
        
        int i = 0;
        while (i < s.length()) {
            if (s.charAt(i) == 'D') {
                int j = i;
                while (j < s.length() && s.charAt(j) == 'D') {
                    j++;
                }
                reverse(result, i, j);
                i = j;
            } else {
                i++;
            }
        }
        
        return result;
    }
    
    private void reverse(int[] arr, int start, int end) {
        while (start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
}