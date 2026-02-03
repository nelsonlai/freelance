/*
 * Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        vector<int> criticalPoints;
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1;
        
        while (curr->next) {
            // Check if current is a critical point
            if ((prev->val < curr->val && curr->val > curr->next->val) ||
                (prev->val > curr->val && curr->val < curr->next->val)) {
                criticalPoints.push_back(index);
            }
            
            prev = curr;
            curr = curr->next;
            index++;
        }
        
        if (criticalPoints.size() < 2) {
            return {-1, -1};
        }
        
        // Minimum distance is between consecutive critical points
        int minDist = INT_MAX;
        for (int i = 1; i < criticalPoints.size(); i++) {
            minDist = min(minDist, criticalPoints[i] - criticalPoints[i - 1]);
        }
        
        // Maximum distance is between first and last
        int maxDist = criticalPoints.back() - criticalPoints[0];
        
        return {minDist, maxDist};
    }
};