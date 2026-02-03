/*
 * Problem: Top K Frequent Elements
 * Difficulty: Medium
 * Tags: array, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        priority_queue<pair<int, int>> heap;
        for (auto& entry : count) {
            heap.push({entry.second, entry.first});
        }
        
        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(heap.top().second);
            heap.pop();
        }
        return result;
    }
};