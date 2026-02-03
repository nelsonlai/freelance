/**
 * Problem: Expression Add Operators
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> addOperators(String num, int target) {
        List<String> result = new ArrayList<>();
        backtrack(num, target, 0, "", 0, 0, result);
        return result;
    }
    
    private void backtrack(String num, int target, int index, String path, 
                          long value, long prev, List<String> result) {
        if (index == num.length()) {
            if (value == target) {
                result.add(path);
            }
            return;
        }
        
        for (int i = index; i < num.length(); i++) {
            if (i > index && num.charAt(index) == '0') {
                break;
            }
            
            long curr = Long.parseLong(num.substring(index, i + 1));
            
            if (index == 0) {
                backtrack(num, target, i + 1, String.valueOf(curr), curr, curr, result);
            } else {
                backtrack(num, target, i + 1, path + "+" + curr, value + curr, curr, result);
                backtrack(num, target, i + 1, path + "-" + curr, value - curr, -curr, result);
                backtrack(num, target, i + 1, path + "*" + curr, value - prev + prev * curr, prev * curr, result);
            }
        }
    }
}