/*
 * Problem: Add Binary
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        
        while (i >= 0 || j >= 0 || carry > 0) {
            int total = carry;
            if (i >= 0) {
                total += a[i--] - '0';
            }
            if (j >= 0) {
                total += b[j--] - '0';
            }
            result += (total % 2) + '0';
            carry = total / 2;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};