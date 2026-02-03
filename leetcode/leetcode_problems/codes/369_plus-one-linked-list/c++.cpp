/*
 * Problem: Plus One Linked List
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
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }

public:
    ListNode* plusOne(ListNode* head) {
        head = reverse(head);
        ListNode* node = head;
        int carry = 1;
        ListNode* prev = nullptr;
        
        while (node) {
            node->val += carry;
            carry = node->val / 10;
            node->val %= 10;
            prev = node;
            node = node->next;
        }
        
        if (carry) {
            prev->next = new ListNode(carry);
        }
        
        return reverse(head);
    }
};