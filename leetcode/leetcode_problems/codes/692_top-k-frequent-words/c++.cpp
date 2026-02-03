/*
 * Problem: Top K Frequent Words
 * Difficulty: Medium
 * Tags: array, string, graph, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count;
        for (string word : words) {
            count[word]++;
        }
        
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        };
        
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> heap(cmp);
        
        for (auto& entry : count) {
            heap.push(entry);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        vector<string> result;
        while (!heap.empty()) {
            result.push_back(heap.top().first);
            heap.pop();
        }
        reverse(result.begin(), result.end());
        
        return result;
    }
};