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
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwo(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = NULL;
    struct ListNode* current = dummy;
    
    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    
    current->next = (l1 != NULL) ? l1 : l2;
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) {
        return NULL;
    }
    
    while (listsSize > 1) {
        int newSize = (listsSize + 1) / 2;
        for (int i = 0; i < listsSize / 2; i++) {
            lists[i] = mergeTwo(lists[i], lists[i + newSize]);
        }
        listsSize = newSize;
    }
    
    return lists[0];
}