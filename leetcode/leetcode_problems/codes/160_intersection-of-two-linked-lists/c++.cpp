/*
 * Problem: Intersection of Two Linked Lists
 * Difficulty: Easy
 * Tags: array, hash, linked_list
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) {
            return nullptr;
        }
        
        ListNode* a = headA;
        ListNode* b = headB;
        
        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        
        return a;
    }
};