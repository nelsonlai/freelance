/**
 * Problem: Minimum Possible Integer After at Most K Adjacent Swaps On Digits
 * Difficulty: Hard
 * Tags: string, tree, greedy
 * 
 * Approach: Greedy - for each position, find smallest digit within k swaps, move it to front
 * Time Complexity: O(n^2) where n is length of num
 * Space Complexity: O(n) for result
 */

class Solution {
    public String minInteger(String num, int k) {
        char[] arr = num.toCharArray();
        int n = arr.length;
        
        for (int i = 0; i < n && k > 0; i++) {
            char minDigit = arr[i];
            int minIdx = i;
            
            for (int j = i + 1; j < Math.min(i + k + 1, n); j++) {
                if (arr[j] < minDigit) {
                    minDigit = arr[j];
                    minIdx = j;
                }
            }
            
            if (minIdx > i) {
                k -= (minIdx - i);
                for (int j = minIdx; j > i; j--) {
                    char temp = arr[j];
                    arr[j] = arr[j-1];
                    arr[j-1] = temp;
                }
            }
        }
        
        return new String(arr);
    }
}