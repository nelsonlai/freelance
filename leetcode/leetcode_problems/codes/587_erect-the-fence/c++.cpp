/*
 * Problem: Erect the Fence
 * Difficulty: Hard
 * Tags: array, tree, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
private:
    int cross(vector<int>& o, vector<int>& a, vector<int>& b) {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }

public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(), trees.end());
        
        vector<vector<int>> lower;
        for (auto& tree : trees) {
            while (lower.size() >= 2 && cross(lower[lower.size()-2], lower[lower.size()-1], tree) < 0) {
                lower.pop_back();
            }
            lower.push_back(tree);
        }
        
        vector<vector<int>> upper;
        for (int i = trees.size() - 1; i >= 0; i--) {
            while (upper.size() >= 2 && cross(upper[upper.size()-2], upper[upper.size()-1], trees[i]) < 0) {
                upper.pop_back();
            }
            upper.push_back(trees[i]);
        }
        
        set<vector<int>> result;
        for (int i = 0; i < lower.size() - 1; i++) {
            result.insert(lower[i]);
        }
        for (int i = 0; i < upper.size() - 1; i++) {
            result.insert(upper[i]);
        }
        
        return vector<vector<int>>(result.begin(), result.end());
    }
};