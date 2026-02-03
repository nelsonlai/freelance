/*
 * Problem: Last Moment Before All Ants Fall Out of a Plank
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int max_left = left.empty() ? 0 : *max_element(left.begin(), left.end());
        int min_right = right.empty() ? n : *min_element(right.begin(), right.end());
        return max(max_left, n - min_right);
    }
};