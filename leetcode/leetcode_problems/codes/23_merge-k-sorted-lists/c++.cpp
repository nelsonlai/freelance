/*
 * Problem: Merge k Sorted Lists
 * Difficulty: Hard
 * Tags: array, sort, linked_list, queue, heap
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
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <vector>
#include <queue>
using namespace std;

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        
        priority_queue<ListNode*, vector<ListNode*>, Compare> heap;
        
        for (ListNode* node : lists) {
            if (node != nullptr) {
                heap.push(node);
            }
        }
        
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        
        while (!heap.empty()) {
            ListNode* node = heap.top();
            heap.pop();
            current->next = node;
            current = current->next;
            
            if (node->next != nullptr) {
                heap.push(node->next);
            }
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};