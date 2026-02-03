/*
 * Problem: Range Addition
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> result(length, 0);
        
        for (auto& update : updates) {
            int start = update[0];
            int end = update[1];
            int inc = update[2];
            result[start] += inc;
            if (end + 1 < length) {
                result[end + 1] -= inc;
            }
        }
        
        for (int i = 1; i < length; i++) {
            result[i] += result[i - 1];
        }
        
        return result;
    }
};