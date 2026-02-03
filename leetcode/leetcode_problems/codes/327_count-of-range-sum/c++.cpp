/*
 * Problem: Count of Range Sum
 * Difficulty: Hard
 * Tags: array, tree, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int mergeSort(vector<long>& prefix, int left, int right, int lower, int upper) {
        if (left >= right) {
            return 0;
        }
        
        int mid = (left + right) / 2;
        int count = mergeSort(prefix, left, mid, lower, upper) + 
                   mergeSort(prefix, mid + 1, right, lower, upper);
        
        int i = mid + 1, j = mid + 1;
        for (int k = left; k <= mid; k++) {
            while (i <= right && prefix[i] - prefix[k] < lower) i++;
            while (j <= right && prefix[j] - prefix[k] <= upper) j++;
            count += j - i;
        }
        
        sort(prefix.begin() + left, prefix.begin() + right + 1);
        return count;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> prefix(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        return mergeSort(prefix, 0, prefix.size() - 1, lower, upper);
    }
};