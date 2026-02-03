/*
 * Problem: Brick Wall
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> count;
        
        for (auto& row : wall) {
            int prefix = 0;
            for (int i = 0; i < row.size() - 1; i++) {
                prefix += row[i];
                count[prefix]++;
            }
        }
        
        int maxCount = 0;
        for (auto& entry : count) {
            maxCount = max(maxCount, entry.second);
        }
        
        return wall.size() - maxCount;
    }
};