/*
 * Problem: Path Sum IV
 * Difficulty: Medium
 * Tags: array, tree, hash, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    int result = 0;
    
    void dfs(unordered_map<string, int>& tree, int depth, int pos, int pathSum) {
        string key = to_string(depth) + "," + to_string(pos);
        if (tree.find(key) == tree.end()) {
            return;
        }
        
        pathSum += tree[key];
        
        string leftKey = to_string(depth + 1) + "," + to_string(2 * pos - 1);
        string rightKey = to_string(depth + 1) + "," + to_string(2 * pos);
        
        if (tree.find(leftKey) == tree.end() && tree.find(rightKey) == tree.end()) {
            result += pathSum;
            return;
        }
        
        if (tree.find(leftKey) != tree.end()) {
            dfs(tree, depth + 1, 2 * pos - 1, pathSum);
        }
        if (tree.find(rightKey) != tree.end()) {
            dfs(tree, depth + 1, 2 * pos, pathSum);
        }
    }

public:
    int pathSum(vector<int>& nums) {
        unordered_map<string, int> tree;
        for (int num : nums) {
            int depth = num / 100;
            int pos = (num / 10) % 10;
            int val = num % 10;
            tree[to_string(depth) + "," + to_string(pos)] = val;
        }
        
        dfs(tree, 1, 1, 0);
        return result;
    }
};