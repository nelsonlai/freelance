/*
 * Problem: Degree of an Array
 * Difficulty: Easy
 * Tags: array, hash
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
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> first, count;
        int maxCount = 0;
        int result = nums.size();
        
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            if (first.find(num) == first.end()) {
                first[num] = i;
            }
            count[num]++;
            
            if (count[num] > maxCount) {
                maxCount = count[num];
                result = i - first[num] + 1;
            } else if (count[num] == maxCount) {
                result = min(result, i - first[num] + 1);
            }
        }
        
        return result;
    }
};