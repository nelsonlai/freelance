/*
 * Problem: Max Difference You Can Get From Changing an Integer
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: For max, replace first non-9 digit with 9. For min, replace first non-0/1 digit with 0/1
 * Time Complexity: O(log num)
 * Space Complexity: O(log num)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDiff(int num) {
        string s = to_string(num);
        
        string maxStr = s;
        for (char c : s) {
            if (c != '9') {
                replace(maxStr.begin(), maxStr.end(), c, '9');
                break;
            }
        }
        
        string minStr = s;
        if (s[0] != '1') {
            char first = s[0];
            replace(minStr.begin(), minStr.end(), first, '1');
        } else {
            for (int i = 1; i < s.length(); i++) {
                char c = s[i];
                if (c != '0' && c != '1') {
                    replace(minStr.begin(), minStr.end(), c, '0');
                    break;
                }
            }
        }
        
        return stoi(maxStr) - stoi(minStr);
    }
};