/**
 * Problem: Product of Two Run-Length Encoded Arrays
 * Difficulty: Medium
 * Tags: array, two pointers
 * 
 * Approach: Two pointers to process both encoded arrays, merge consecutive same values
 * Time Complexity: O(n + m) where n, m are encoded lengths
 * Space Complexity: O(1) excluding output
 */

import java.util.*;

class Solution {
    public List<List<Integer>> findRLEArray(int[][] encoded1, int[][] encoded2) {
        List<List<Integer>> result = new ArrayList<>();
        int i = 0, j = 0;
        
        while (i < encoded1.length && j < encoded2.length) {
            int val1 = encoded1[i][0];
            int count1 = encoded1[i][1];
            int val2 = encoded2[j][0];
            int count2 = encoded2[j][1];
            
            int product = val1 * val2;
            int minCount = Math.min(count1, count2);
            
            if (!result.isEmpty() && result.get(result.size() - 1).get(0) == product) {
                result.get(result.size() - 1).set(1, result.get(result.size() - 1).get(1) + minCount);
            } else {
                result.add(Arrays.asList(product, minCount));
            }
            
            encoded1[i][1] -= minCount;
            encoded2[j][1] -= minCount;
            
            if (encoded1[i][1] == 0) i++;
            if (encoded2[j][1] == 0) j++;
        }
        
        return result;
    }
}