/*
 * Problem: K-diff Pairs in an Array
 * Difficulty: Medium
 * Tags: array, hash, sort, search
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
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        int result = 0;
        if (k == 0) {
            for (auto& entry : count) {
                if (entry.second > 1) {
                    result++;
                }
            }
        } else {
            for (auto& entry : count) {
                if (count.find(entry.first + k) != count.end()) {
                    result++;
                }
            }
        }
        
        return result;
    }
};