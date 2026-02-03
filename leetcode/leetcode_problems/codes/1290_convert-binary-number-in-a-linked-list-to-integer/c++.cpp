/*
 * Problem: Convert Binary Number in a Linked List to Integer
 * Difficulty: Easy
 * Tags: graph, math, linked_list
 * 
 * Approach: Traverse linked list, build binary number, convert to decimal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(1)
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
    int getDecimalValue(ListNode* head) {
        int result = 0;
        while (head != nullptr) {
            result = result * 2 + head->val;
            head = head->next;
        }
        return result;
    }
};
