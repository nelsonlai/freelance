/*
 * Problem: Encode N-ary Tree to Binary Tree
 * Difficulty: Hard
 * Tags: tree, search
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if (!root) {
            return nullptr;
        }
        
        TreeNode* binaryRoot = new TreeNode(root->val);
        
        if (!root->children.empty()) {
            binaryRoot->left = encode(root->children[0]);
            TreeNode* current = binaryRoot->left;
            for (int i = 1; i < root->children.size(); i++) {
                current->right = encode(root->children[i]);
                current = current->right;
            }
        }
        
        return binaryRoot;
    }
	
    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if (!root) {
            return nullptr;
        }
        
        Node* naryRoot = new Node(root->val, {});
        
        if (root->left) {
            Node* child = decode(root->left);
            naryRoot->children.push_back(child);
            TreeNode* current = root->left;
            while (current->right) {
                child = decode(current->right);
                naryRoot->children.push_back(child);
                current = current->right;
            }
        }
        
        return naryRoot;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));