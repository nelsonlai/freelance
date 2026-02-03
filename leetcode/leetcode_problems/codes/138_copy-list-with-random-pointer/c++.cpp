/*
 * Problem: Copy List with Random Pointer
 * Difficulty: Medium
 * Tags: hash, linked_list
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

#include <unordered_map>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        unordered_map<Node*, Node*> oldToNew;
        Node* current = head;
        
        while (current != nullptr) {
            oldToNew[current] = new Node(current->val);
            current = current->next;
        }
        
        current = head;
        while (current != nullptr) {
            oldToNew[current]->next = oldToNew[current->next];
            oldToNew[current]->random = oldToNew[current->random];
            current = current->next;
        }
        
        return oldToNew[head];
    }
};