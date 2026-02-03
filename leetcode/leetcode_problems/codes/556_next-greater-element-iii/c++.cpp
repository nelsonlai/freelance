/*
 * Problem: Next Greater Element III
 * Difficulty: Medium
 * Tags: array, string, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        string digits = to_string(n);
        
        int i = digits.length() - 2;
        while (i >= 0 && digits[i] >= digits[i + 1]) {
            i--;
        }
        
        if (i < 0) {
            return -1;
        }
        
        int j = digits.length() - 1;
        while (digits[j] <= digits[i]) {
            j--;
        }
        
        swap(digits[i], digits[j]);
        reverse(digits.begin() + i + 1, digits.end());
        
        long long result = stoll(digits);
        return result <= INT_MAX ? (int)result : -1;
    }
};