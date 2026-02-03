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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int length = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }
        
        int partSize = length / k;
        int extra = length % k;
        vector<ListNode*> result(k, nullptr);
        curr = head;
        
        for (int i = 0; i < k; i++) {
            result[i] = curr;
            int currentSize = partSize + (i < extra ? 1 : 0);
            for (int j = 0; j < currentSize - 1; j++) {
                if (curr != nullptr) {
                    curr = curr->next;
                }
            }
            if (curr != nullptr) {
                ListNode* next = curr->next;
                curr->next = nullptr;
                curr = next;
            }
        }
        
        return result;
    }
};
