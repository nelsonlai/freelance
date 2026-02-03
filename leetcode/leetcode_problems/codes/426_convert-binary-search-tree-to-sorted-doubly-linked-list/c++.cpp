/*
 * Problem: Convert Binary Search Tree to Sorted Doubly Linked List
 * Difficulty: Medium
 * Tags: tree, sort, search, linked_list, stack
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
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
private:
    Node* first = nullptr;
    Node* last = nullptr;
    
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            
            if (last) {
                last->right = node;
                node->left = last;
            } else {
                first = node;
            }
            last = node;
            
            inorder(node->right);
        }
    }

public:
    Node* treeToDoublyList(Node* root) {
        if (!root) {
            return nullptr;
        }
        
        inorder(root);
        
        first->left = last;
        last->right = first;
        
        return first;
    }
};