#include <string>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* str2tree(string s) {
        if (s.empty()) {
            return nullptr;
        }
        
        int i = 0;
        while (i < s.length() && (isdigit(s[i]) || s[i] == '-')) {
            i++;
        }
        
        int val = stoi(s.substr(0, i));
        TreeNode* root = new TreeNode(val);
        
        if (i < s.length() && s[i] == '(') {
            i++;
            int start = i;
            int count = 1;
            while (i < s.length() && count > 0) {
                if (s[i] == '(') {
                    count++;
                } else if (s[i] == ')') {
                    count--;
                }
                i++;
            }
            root->left = str2tree(s.substr(start, i - 1 - start));
        }
        
        if (i < s.length() && s[i] == '(') {
            i++;
            int start = i;
            int count = 1;
            while (i < s.length() && count > 0) {
                if (s[i] == '(') {
                    count++;
                } else if (s[i] == ')') {
                    count--;
                }
                i++;
            }
            root->right = str2tree(s.substr(start, i - 1 - start));
        }
        
        return root;
    }
};
