/*
 * Problem: Remove Nth Node From End of List
 * Difficulty: Medium
 * Tags: array, linked_list
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* first = dummy;
        ListNode* second = dummy;
        
        for (int i = 0; i <= n; i++) {
            first = first->next;
        }
        
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }
        
        second->next = second->next->next;
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};