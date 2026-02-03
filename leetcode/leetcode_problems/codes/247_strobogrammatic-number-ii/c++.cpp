/*
 * Problem: Strobogrammatic Number II
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<string> helper(int m, int n) {
        if (m == 0) {
            return {""};
        }
        if (m == 1) {
            return {"0", "1", "8"};
        }
        
        vector<string> prev = helper(m - 2, n);
        vector<string> result;
        for (string s : prev) {
            if (m != n) {
                result.push_back("0" + s + "0");
            }
            result.push_back("1" + s + "1");
            result.push_back("6" + s + "9");
            result.push_back("8" + s + "8");
            result.push_back("9" + s + "6");
        }
        return result;
    }

public:
    vector<string> findStrobogrammatic(int n) {
        return helper(n, n);
    }
};