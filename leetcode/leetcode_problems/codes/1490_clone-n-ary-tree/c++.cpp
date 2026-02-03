/*
 * Problem: Clone N-ary Tree
 * Difficulty: Medium
 * Tags: tree, graph, hash, search
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

class Solution {
public:
    Node* cloneTree(Node* root) {
        if (!root) {
            return nullptr;
        }
        
        Node* newRoot = new Node(root->val);
        for (Node* child : root->children) {
            newRoot->children.push_back(cloneTree(child));
        }
        
        return newRoot;
    }
};