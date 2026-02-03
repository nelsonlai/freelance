/*
 * Problem: Reverse Nodes in k-Group
 * Difficulty: Hard
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
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* current = head;
    int count = 0;
    
    while (current != NULL && count < k) {
        current = current->next;
        count++;
    }
    
    if (count == k) {
        current = reverseKGroup(current, k);
        
        while (count > 0) {
            struct ListNode* next = head->next;
            head->next = current;
            current = head;
            head = next;
            count--;
        }
        head = current;
    }
    
    return head;
}