/*
 * Problem: Distinct Numbers in Each Subarray
 * Difficulty: Medium
 * Tags: array, hash, sliding window
 * 
 * Approach: Sliding window with frequency map
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(k)
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> distinctNumbers(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            count[nums[i]]++;
            
            if (i >= k - 1) {
                result.push_back(count.size());
                
                int left = nums[i - k + 1];
                count[left]--;
                if (count[left] == 0) {
                    count.erase(left);
                }
            }
        }
        
        return result;
    }
};