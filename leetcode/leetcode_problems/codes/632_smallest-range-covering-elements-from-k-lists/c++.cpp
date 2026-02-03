/*
 * Problem: Smallest Range Covering Elements from K Lists
 * Difficulty: Hard
 * Tags: array, greedy, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        int maxVal = INT_MIN;
        
        for (int i = 0; i < nums.size(); i++) {
            heap.push({nums[i][0], i, 0});
            maxVal = max(maxVal, nums[i][0]);
        }
        
        vector<int> result = {heap.top()[0], maxVal};
        
        while (true) {
            auto curr = heap.top();
            heap.pop();
            int val = curr[0], listIdx = curr[1], idx = curr[2];
            
            if (maxVal - val < result[1] - result[0]) {
                result[0] = val;
                result[1] = maxVal;
            }
            
            if (idx + 1 >= nums[listIdx].size()) {
                break;
            }
            
            int nextVal = nums[listIdx][idx + 1];
            maxVal = max(maxVal, nextVal);
            heap.push({nextVal, listIdx, idx + 1});
        }
        
        return result;
    }
};