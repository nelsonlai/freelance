/**
 * Problem: Largest Number After Mutating Substring
 * Difficulty: Medium
 * Tags: array, string, greedy
 * 
 * Approach: Greedily mutate substring where change[i] > digit
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public String maximumNumber(String num, int[] change) {
        char[] numArr = num.toCharArray();
        boolean mutated = false;
        
        for (int i = 0; i < numArr.length; i++) {
            int digit = numArr[i] - '0';
            if (change[digit] > digit) {
                numArr[i] = (char) ('0' + change[digit]);
                mutated = true;
            } else if (change[digit] < digit && mutated) {
                break;
            }
        }
        
        return new String(numArr);
    }
}