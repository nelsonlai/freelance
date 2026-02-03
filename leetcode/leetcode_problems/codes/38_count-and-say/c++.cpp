/*
 * Problem: Count and Say
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        
        string result = "1";
        for (int i = 1; i < n; i++) {
            string newResult = "";
            int j = 0;
            while (j < result.length()) {
                int count = 1;
                while (j + 1 < result.length() && result[j] == result[j + 1]) {
                    count++;
                    j++;
                }
                newResult += to_string(count);
                newResult += result[j];
                j++;
            }
            result = newResult;
        }
        
        return result;
    }
};