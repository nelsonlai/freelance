/*
 * Problem: Diameter of N-Ary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - return max depth, diameter is max of (max1 + max2) across all nodes
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
 */

#include <vector>
#include <algorithm>

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
private:
    int maxDiameter = 0;
    
    int dfs(Node* node) {
        if (!node || node->children.empty()) {
            return 0;
        }
        
        vector<int> depths;
        for (Node* child : node->children) {
            depths.push_back(dfs(child));
        }
        
        sort(depths.rbegin(), depths.rend());
        
        if (depths.size() >= 2) {
            maxDiameter = std::max(maxDiameter, depths[0] + depths[1] + 2);
        } else if (depths.size() == 1) {
            maxDiameter = std::max(maxDiameter, depths[0] + 1);
        }
        
        return depths.empty() ? 0 : depths[0] + 1;
    }

public:
    int diameter(Node* root) {
        maxDiameter = 0;
        dfs(root);
        return maxDiameter;
    }
};