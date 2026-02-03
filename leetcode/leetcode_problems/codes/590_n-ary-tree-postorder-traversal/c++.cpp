/*
 * Problem: N-ary Tree Postorder Traversal
 * Difficulty: Easy
 * Tags: tree, search, stack
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

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

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> postorder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        
        vector<int> result;
        
        for (Node* child : root->children) {
            vector<int> childResult = postorder(child);
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
        
        result.push_back(root->val);
        return result;
    }
};