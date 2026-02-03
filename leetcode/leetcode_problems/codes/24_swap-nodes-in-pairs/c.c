/*
 * Problem: Swap Nodes in Pairs
 * Difficulty: Medium
 * Tags: linked_list
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
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = head;
    struct ListNode* prev = dummy;
    
    while (prev->next != NULL && prev->next->next != NULL) {
        struct ListNode* first = prev->next;
        struct ListNode* second = prev->next->next;
        
        prev->next = second;
        first->next = second->next;
        second->next = first;
        
        prev = first;
    }
    
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}