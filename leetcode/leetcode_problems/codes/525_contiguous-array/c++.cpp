/*
 * Problem: Contiguous Array
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
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> countMap;
        countMap[0] = -1;
        int count = 0;
        int maxLength = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i] == 1 ? 1 : -1;
            if (countMap.find(count) != countMap.end()) {
                maxLength = max(maxLength, i - countMap[count]);
            } else {
                countMap[count] = i;
            }
        }
        
        return maxLength;
    }
};