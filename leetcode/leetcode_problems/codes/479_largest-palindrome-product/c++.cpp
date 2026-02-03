/*
 * Problem: Largest Palindrome Product
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        
        long long maxNum = pow(10, n) - 1;
        long long minNum = pow(10, n - 1);
        
        for (long long i = maxNum; i >= minNum; i--) {
            string left = to_string(i);
            string right = left;
            reverse(right.begin(), right.end());
            string palindromeStr = left + right;
            long long palindrome = stoll(palindromeStr);
            
            for (long long j = maxNum; j * j >= palindrome; j--) {
                if (palindrome % j == 0 && palindrome / j >= minNum && palindrome / j <= maxNum) {
                    return (int)(palindrome % 1337);
                }
            }
        }
        
        return 0;
    }
};