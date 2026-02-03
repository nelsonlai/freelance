/*
 * Problem: Depth of BST Given Insertion Order
 * Difficulty: Medium
 * Tags: array, tree, search, binary search tree
 * 
 * Approach: Use set with binary search to track depths
 * Time Complexity: O(n log n) worst case
 * Space Complexity: O(n)
 */

#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        map<int, int> depths;
        set<int> sortedKeys;
        int maxDepth = 0;
        
        for (int val : order) {
            auto it = sortedKeys.lower_bound(val);
            int depth = 1;
            
            if (it != sortedKeys.begin()) {
                auto prevIt = prev(it);
                depth = max(depth, depths[*prevIt] + 1);
            }
            if (it != sortedKeys.end()) {
                depth = max(depth, depths[*it] + 1);
            }
            
            sortedKeys.insert(val);
            depths[val] = depth;
            maxDepth = max(maxDepth, depth);
        }
        
        return maxDepth;
    }
};