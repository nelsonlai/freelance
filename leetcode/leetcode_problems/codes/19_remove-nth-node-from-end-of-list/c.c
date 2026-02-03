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
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = head;
    
    struct ListNode* first = dummy;
    struct ListNode* second = dummy;
    
    for (int i = 0; i <= n; i++) {
        first = first->next;
    }
    
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }
    
    struct ListNode* toDelete = second->next;
    second->next = second->next->next;
    free(toDelete);
    
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}