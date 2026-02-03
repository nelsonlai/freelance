/*
 * Problem: Additive Number
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <climits>

using namespace std;

class Solution {
private:
    bool isValid(long num1, long num2, string& num, int start) {
        if (start == num.length()) return true;
        
        long sum = num1 + num2;
        string sumStr = to_string(sum);
        
        if (num.substr(start, sumStr.length()) != sumStr) return false;
        
        return isValid(num2, sum, num, start + sumStr.length());
    }

public:
    bool isAdditiveNumber(string num) {
        int n = num.length();
        for (int i = 1; i <= n / 2; i++) {
            if (num[0] == '0' && i > 1) break;
            long num1 = stol(num.substr(0, i));
            
            for (int j = i + 1; j < n; j++) {
                if (num[i] == '0' && j > i + 1) break;
                long num2 = stol(num.substr(i, j - i));
                
                if (isValid(num1, num2, num, j)) {
                    return true;
                }
            }
        }
        return false;
    }
};