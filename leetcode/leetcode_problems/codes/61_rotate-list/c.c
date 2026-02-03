/*
 * Problem: Rotate List
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
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }
    
    // Find length and get tail
    int length = 1;
    struct ListNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }
    
    k = k % length;
    if (k == 0) {
        return head;
    }
    
    // Find new tail
    struct ListNode* newTail = head;
    for (int i = 0; i < length - k - 1; i++) {
        newTail = newTail->next;
    }
    
    // Rotate
    struct ListNode* newHead = newTail->next;
    newTail->next = NULL;
    tail->next = head;
    
    return newHead;
}