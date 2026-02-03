/*
 * Problem: Three Consecutive Odds
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        for (int i = 0; i < (int)arr.size() - 2; i++) {
            if (arr[i] % 2 == 1 && arr[i+1] % 2 == 1 && arr[i+2] % 2 == 1) {
                return true;
            }
        }
        return false;
    }
};