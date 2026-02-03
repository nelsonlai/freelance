/*
 * Problem: Flatten a Multilevel Doubly Linked List
 * Difficulty: Medium
 * Tags: search, linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
private:
    Node* flattenHelper(Node* node) {
        Node* current = node;
        Node* tail = node;
        
        while (current) {
            Node* next = current->next;
            if (current->child) {
                Node* childTail = flattenHelper(current->child);
                current->next = current->child;
                current->child->prev = current;
                childTail->next = next;
                if (next) {
                    next->prev = childTail;
                }
                current->child = nullptr;
                tail = childTail;
            } else {
                tail = current;
            }
            current = next;
        }
        
        return tail;
    }

public:
    Node* flatten(Node* head) {
        if (!head) {
            return nullptr;
        }
        
        flattenHelper(head);
        return head;
    }
};