/*
 * Problem: Palindrome Linked List
 * Difficulty: Easy
 * Tags: array, string, linked_list, stack
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
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode* prev = nullptr;
        while (slow) {
            ListNode* nextTemp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = nextTemp;
        }
        
        ListNode* left = head;
        ListNode* right = prev;
        while (right) {
            if (left->val != right->val) {
                return false;
            }
            left = left->next;
            right = right->next;
        }
        
        return true;
    }
};