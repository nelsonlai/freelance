/*
 * Problem: Add Two Numbers
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
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = NULL;
    struct ListNode* current = dummy;
    int carry = 0;
    
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int val1 = l1 != NULL ? l1->val : 0;
        int val2 = l2 != NULL ? l2->val : 0;
        int sum = val1 + val2 + carry;
        carry = sum / 10;
        
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = NULL;
        current->next = newNode;
        current = current->next;
        
        l1 = l1 != NULL ? l1->next : NULL;
        l2 = l2 != NULL ? l2->next : NULL;
    }
    
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}