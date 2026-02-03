/*
 * Problem: K Empty Slots
 * Difficulty: Hard
 * Tags: array, tree, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        int n = bulbs.size();
        vector<int> days(n);
        for (int day = 0; day < n; day++) {
            days[bulbs[day] - 1] = day + 1;
        }
        
        int left = 0, right = k + 1;
        int result = INT_MAX;
        
        while (right < n) {
            int maxDay = max(days[left], days[right]);
            bool valid = true;
            
            for (int i = left + 1; i < right; i++) {
                if (days[i] < maxDay) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                result = min(result, maxDay);
            }
            
            left = right;
            right = left + k + 1;
        }
        
        return result == INT_MAX ? -1 : result;
    }
};