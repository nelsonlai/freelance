/*
 * Problem: Maximum Swap
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: Greedy algorithm with local optimal choices
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        string digits = to_string(num);
        vector<int> last(10, -1);
        
        for (int i = 0; i < digits.length(); i++) {
            last[digits[i] - '0'] = i;
        }
        
        for (int i = 0; i < digits.length(); i++) {
            for (int d = 9; d > digits[i] - '0'; d--) {
                if (last[d] > i) {
                    swap(digits[i], digits[last[d]]);
                    return stoi(digits);
                }
            }
        }
        
        return num;
    }
};