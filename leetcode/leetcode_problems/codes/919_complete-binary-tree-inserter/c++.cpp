#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class CBTInserter {
private:
    TreeNode* root;
    queue<TreeNode*> q;
    
public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        queue<TreeNode*> temp;
        temp.push(root);
        
        while (!temp.empty()) {
            TreeNode* node = temp.front();
            temp.pop();
            if (!node->left || !node->right) {
                q.push(node);
            }
            if (node->left) {
                temp.push(node->left);
            }
            if (node->right) {
                temp.push(node->right);
            }
        }
    }
    
    int insert(int val) {
        TreeNode* parent = q.front();
        TreeNode* newNode = new TreeNode(val);
        
        if (!parent->left) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
            q.pop();
        }
        
        q.push(newNode);
        return parent->val;
    }
    
    TreeNode* get_root() {
        return root;
    }
};
