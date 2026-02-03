/*
 * Problem: Sequence Reconstruction
 * Difficulty: Medium
 * Tags: array, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> inDegree;
        
        for (auto& seq : sequences) {
            for (int i = 0; i < seq.size() - 1; i++) {
                graph[seq[i]].push_back(seq[i + 1]);
                inDegree[seq[i + 1]]++;
                if (inDegree.find(seq[i]) == inDegree.end()) {
                    inDegree[seq[i]] = 0;
                }
            }
        }
        
        queue<int> q;
        for (int num : nums) {
            if (inDegree[num] == 0) {
                q.push(num);
            }
        }
        
        vector<int> result;
        while (!q.empty()) {
            if (q.size() > 1) {
                return false;
            }
            int node = q.front();
            q.pop();
            result.push_back(node);
            
            for (int neighbor : graph[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        if (result.size() != nums.size()) {
            return false;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (result[i] != nums[i]) {
                return false;
            }
        }
        
        return true;
    }
};