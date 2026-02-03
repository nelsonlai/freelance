/*
 * Problem: Range Sum Query - Immutable
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class NumArray {
private:
    vector<int> prefixSum;

public:
    NumArray(vector<int>& nums) {
        prefixSum.push_back(0);
        for (int num : nums) {
            prefixSum.push_back(prefixSum.back() + num);
        }
    }
    
    int sumRange(int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */