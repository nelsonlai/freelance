/**
 * Problem: Greatest Common Divisor of Strings
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: Check if strings are divisible, then find GCD of lengths
 * Time Complexity: O(n + m) where n and m are string lengths
 * Space Complexity: O(1)
 */

class Solution {
    public String gcdOfStrings(String str1, String str2) {
        if (!(str1 + str2).equals(str2 + str1)) {
            return "";
        }
        
        int gcdLen = gcd(str1.length(), str2.length());
        return str1.substring(0, gcdLen);
    }
    
    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}