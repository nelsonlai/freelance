/*
 * Problem: Count of Smaller Numbers After Self
 * Difficulty: Hard
 * Tags: array, tree, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>

using namespace std;

class Solution {
private:
    void mergeSort(vector<int>& nums, vector<int>& indices, vector<int>& result, int left, int right) {
        if (left >= right) return;
        
        int mid = (left + right) / 2;
        mergeSort(nums, indices, result, left, mid);
        mergeSort(nums, indices, result, mid + 1, right);
        
        vector<int> merged(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        int rightCount = 0;
        
        while (i <= mid && j <= right) {
            if (nums[indices[j]] < nums[indices[i]]) {
                rightCount++;
                merged[k++] = indices[j++];
            } else {
                result[indices[i]] += rightCount;
                merged[k++] = indices[i++];
            }
        }
        
        while (i <= mid) {
            result[indices[i]] += rightCount;
            merged[k++] = indices[i++];
        }
        
        while (j <= right) {
            merged[k++] = indices[j++];
        }
        
        for (int idx = 0; idx < merged.size(); idx++) {
            indices[left + idx] = merged[idx];
        }
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 0);
        vector<int> indices(n);
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        
        mergeSort(nums, indices, result, 0, n - 1);
        return result;
    }
};