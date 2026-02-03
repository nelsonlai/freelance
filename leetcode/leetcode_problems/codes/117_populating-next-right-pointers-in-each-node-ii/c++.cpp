/*
 * Problem: Populating Next Right Pointers in Each Node II
 * Difficulty: Medium
 * Tags: tree, search, linked_list, stack
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
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }
        
        Node* head = root;
        while (head != nullptr) {
            Node* dummy = new Node(0);
            Node* current = dummy;
            
            while (head != nullptr) {
                if (head->left != nullptr) {
                    current->next = head->left;
                    current = current->next;
                }
                if (head->right != nullptr) {
                    current->next = head->right;
                    current = current->next;
                }
                head = head->next;
            }
            
            head = dummy->next;
        }
        
        return root;
    }
};