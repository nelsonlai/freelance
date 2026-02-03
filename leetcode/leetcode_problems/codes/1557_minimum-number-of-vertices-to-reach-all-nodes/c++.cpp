/*
 * Problem: Minimum Number of Vertices to Reach All Nodes
 * Difficulty: Medium
 * Tags: array, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        unordered_set<int> hasIncoming;
        for (auto& edge : edges) {
            hasIncoming.insert(edge[1]);
        }
        
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (hasIncoming.find(i) == hasIncoming.end()) {
                result.push_back(i);
            }
        }
        return result;
    }
};