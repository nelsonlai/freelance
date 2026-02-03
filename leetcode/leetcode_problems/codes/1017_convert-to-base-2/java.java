/**
 * Problem: Convert to Base -2
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: Convert to base -2 by repeatedly dividing and handling negative remainders
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) for result
 */

import java.util.*;

class Solution {
    public String baseNeg2(int n) {
        if (n == 0) {
            return "0";
        }
        
        List<Integer> result = new ArrayList<>();
        while (n != 0) {
            int remainder = n % -2;
            n /= -2;
            if (remainder < 0) {
                remainder += 2;
                n += 1;
            }
            result.add(remainder);
        }
        
        Collections.reverse(result);
        StringBuilder sb = new StringBuilder();
        for (int digit : result) {
            sb.append(digit);
        }
        return sb.toString();
    }
}