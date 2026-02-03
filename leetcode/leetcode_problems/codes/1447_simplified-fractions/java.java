/**
 * Problem: Simplified Fractions
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: Generate all fractions, only include if GCD(numerator, denominator) == 1
 * Time Complexity: O(n^2 * log n) for GCD calculations
 * Space Complexity: O(n^2) for result
 */

import java.util.*;

class Solution {
    public List<String> simplifiedFractions(int n) {
        List<String> result = new ArrayList<>();
        for (int denominator = 2; denominator <= n; denominator++) {
            for (int numerator = 1; numerator < denominator; numerator++) {
                if (gcd(numerator, denominator) == 1) {
                    result.add(numerator + "/" + denominator);
                }
            }
        }
        return result;
    }
    
    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}