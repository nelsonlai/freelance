/*
 * Problem: Make Two Arrays Equal by Reversing Subarrays
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Check if both arrays have same elements (can always rearrange)
 * Time Complexity: O(n) where n is length of arrays
 * Space Complexity: O(n) for counter
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> count;
        for (int num : target) {
            count[num]++;
        }
        for (int num : arr) {
            count[num]--;
        }
        for (auto& [key, val] : count) {
            if (val != 0) {
                return false;
            }
        }
        return true;
    }
};