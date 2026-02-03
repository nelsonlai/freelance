/*
 * Problem: Sort Linked List Already Sorted Using Absolute Values
 * Difficulty: Medium
 * Tags: array, sort, linked_list
 * 
 * Approach: Separate negative and positive nodes, then merge
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(1)
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* sortLinkedList(ListNode* head) {
        if (!head) {
            return head;
        }
        
        // Separate negative (reverse order) and positive nodes
        ListNode* negHead = nullptr;
        ListNode* posHead = nullptr;
        ListNode* negTail = nullptr;
        ListNode* posTail = nullptr;
        
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = nullptr;
            
            if (curr->val < 0) {
                // Add to negative list (in reverse order)
                if (!negHead) {
                    negHead = curr;
                    negTail = curr;
                } else {
                    curr->next = negHead;
                    negHead = curr;
                }
            } else {
                // Add to positive list (in order)
                if (!posHead) {
                    posHead = curr;
                    posTail = curr;
                } else {
                    posTail->next = curr;
                    posTail = curr;
                }
            }
            
            curr = next;
        }
        
        // Merge negative and positive lists
        if (negHead) {
            if (posHead) {
                negTail->next = posHead;
            }
            return negHead;
        } else {
            return posHead;
        }
    }
};