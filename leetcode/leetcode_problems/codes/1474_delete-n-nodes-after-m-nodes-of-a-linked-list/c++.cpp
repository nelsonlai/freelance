/*
 * Problem: Delete N Nodes After M Nodes of a Linked List
 * Difficulty: Easy
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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode* current = head;
        
        while (current) {
            for (int i = 0; i < m - 1 && current; i++) {
                current = current->next;
            }
            
            if (!current) {
                break;
            }
            
            ListNode* temp = current->next;
            for (int i = 0; i < n && temp; i++) {
                temp = temp->next;
            }
            
            current->next = temp;
            current = temp;
        }
        
        return head;
    }
};