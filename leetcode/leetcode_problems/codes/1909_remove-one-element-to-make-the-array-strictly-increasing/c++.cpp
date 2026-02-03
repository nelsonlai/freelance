/*
 * Problem: Remove One Element to Make the Array Strictly Increasing
 * Difficulty: Easy
 * Tags: array, greedy
 * 
 * Approach: Check if removing one element makes array strictly increasing
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
private:
    bool isStrictlyIncreasing(vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] <= arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
    
public:
    bool canBeIncreasing(vector<int>& nums) {
        if (isStrictlyIncreasing(nums)) {
            return true;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            vector<int> newNums;
            for (int j = 0; j < nums.size(); j++) {
                if (j != i) {
                    newNums.push_back(nums[j]);
                }
            }
            if (isStrictlyIncreasing(newNums)) {
                return true;
            }
        }
        
        return false;
    }
};