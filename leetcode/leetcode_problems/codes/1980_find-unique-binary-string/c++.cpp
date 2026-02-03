/*
 * Problem: Find Unique Binary String
 * Difficulty: Medium
 * Tags: array, string, hash, Cantor's diagonal argument
 * 
 * Approach: Use diagonal argument - flip i-th bit of i-th string
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        string result;
        for (int i = 0; i < nums.size(); i++) {
            // Flip the i-th bit of the i-th string
            if (nums[i][i] == '0') {
                result += '1';
            } else {
                result += '0';
            }
        }
        return result;
    }
};