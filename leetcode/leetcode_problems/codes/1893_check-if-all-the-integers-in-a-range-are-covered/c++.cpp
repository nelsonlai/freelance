/*
 * Problem: Check if All the Integers in a Range Are Covered
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Mark all covered numbers, check if range is fully covered
 * Time Complexity: O(n * range_size) where n is ranges
 * Space Complexity: O(range_size)
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        unordered_set<int> covered;
        for (auto& range : ranges) {
            for (int i = range[0]; i <= range[1]; i++) {
                covered.insert(i);
            }
        }
        
        for (int i = left; i <= right; i++) {
            if (covered.find(i) == covered.end()) {
                return false;
            }
        }
        
        return true;
    }
};