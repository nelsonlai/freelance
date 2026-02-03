/*
 * Problem: Serialize and Deserialize BST
 * Difficulty: Medium
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
#include <vector>
#include <sstream>

using namespace std;

class Codec {
private:
    void preorder(TreeNode* node, vector<string>& result) {
        if (node) {
            result.push_back(to_string(node->val));
            preorder(node->left, result);
            preorder(node->right, result);
        }
    }
    
    TreeNode* build(vector<int>& values, long minVal, long maxVal) {
        if (values.empty() || values[0] < minVal || values[0] > maxVal) {
            return nullptr;
        }
        
        int val = values[0];
        values.erase(values.begin());
        TreeNode* node = new TreeNode(val);
        node->left = build(values, minVal, val);
        node->right = build(values, val, maxVal);
        return node;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        
        vector<string> result;
        preorder(root, result);
        
        stringstream ss;
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) ss << ",";
            ss << result[i];
        }
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        
        vector<int> values;
        stringstream ss(data);
        string item;
        while (getline(ss, item, ',')) {
            values.push_back(stoi(item));
        }
        
        return build(values, LONG_MIN, LONG_MAX);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;