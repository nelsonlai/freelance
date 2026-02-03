/*
 * Problem: Longest Harmonious Subsequence
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        int maxLength = 0;
        for (auto& entry : count) {
            if (count.find(entry.first + 1) != count.end()) {
                maxLength = max(maxLength, entry.second + count[entry.first + 1]);
            }
        }
        
        return maxLength;
    }
};