/*
 * Problem: Can Make Arithmetic Progression From Sequence
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int diff = arr[1] - arr[0];
        for (int i = 2; i < arr.size(); i++) {
            if (arr[i] - arr[i-1] != diff) {
                return false;
            }
        }
        return true;
    }
};