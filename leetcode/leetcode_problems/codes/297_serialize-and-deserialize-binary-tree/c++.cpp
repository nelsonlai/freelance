/*
 * Problem: Serialize and Deserialize Binary Tree
 * Difficulty: Hard
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class Codec {
private:
    string dfs(TreeNode* node) {
        if (!node) {
            return "None,";
        }
        return to_string(node->val) + "," + dfs(node->left) + dfs(node->right);
    }
    
    TreeNode* deserializeHelper(queue<string>& q) {
        string val = q.front();
        q.pop();
        if (val == "None") {
            return nullptr;
        }
        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeHelper(q);
        node->right = deserializeHelper(q);
        return node;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        return dfs(root);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> q;
        stringstream ss(data);
        string item;
        while (getline(ss, item, ',')) {
            q.push(item);
        }
        return deserializeHelper(q);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));