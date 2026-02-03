/*
 * Problem: Linked List Random Node
 * Difficulty: Medium
 * Tags: math, linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     ListNode(int x) : val(x), next(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     ListNode(int x, ListNode *next) : val(x), next(next) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
#include <cstdlib>

class Solution {
private:
    ListNode* head;

public:
    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        int result = 0;
        int count = 0;
        ListNode* current = head;
        
        while (current) {
            count++;
            if (rand() % count == 0) {
                result = current->val;
            }
            current = current->next;
        }
        
        return result;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */