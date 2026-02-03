/**
 * Problem: Fraction Addition and Subtraction
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.regex.*;
import java.math.*;

class Solution {
    public String fractionAddition(String expression) {
        Pattern pattern = Pattern.compile("([+-]?\\d+)/(\\d+)");
        Matcher matcher = pattern.matcher(expression);
        
        long numerator = 0;
        long denominator = 1;
        
        while (matcher.find()) {
            long num = Long.parseLong(matcher.group(1));
            long den = Long.parseLong(matcher.group(2));
            numerator = numerator * den + num * denominator;
            denominator *= den;
        }
        
        if (numerator == 0) {
            return "0/1";
        }
        
        long g = gcd(Math.abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
        
        return numerator + "/" + denominator;
    }
    
    private long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}