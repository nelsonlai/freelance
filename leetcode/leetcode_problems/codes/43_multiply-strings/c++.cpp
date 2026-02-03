/*
 * Problem: Multiply Strings
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        
        int m = num1.length(), n = num2.length();
        vector<int> result(m + n, 0);
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int total = mul + result[p2];
                
                result[p2] = total % 10;
                result[p1] += total / 10;
            }
        }
        
        // Remove leading zeros
        string res;
        int start = 0;
        while (start < result.size() && result[start] == 0) {
            start++;
        }
        for (int i = start; i < result.size(); i++) {
            res += (char)(result[i] + '0');
        }
        
        return res;
    }
};