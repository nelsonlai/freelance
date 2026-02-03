/*
 * Problem: Maximum Number of Ways to Partition an Array
 * Difficulty: Hard
 * Tags: array, hash, prefix sum
 * 
 * Approach: Use prefix sum and hash map to count partitions before/after changing each element
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        int n = nums.size();
        long long total = 0;
        for (int num : nums) {
            total += num;
        }
        
        // Calculate prefix sum
        vector<long long> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }
        
        // Count partitions without changing any element
        int result = 0;
        for (int i = 0; i < n - 1; i++) {
            if (prefix[i] == total - prefix[i]) {
                result++;
            }
        }
        
        // For each position, calculate partitions if we change nums[i] to k
        unordered_map<long long, int> leftCount;
        unordered_map<long long, int> rightCount;
        
        // Initialize rightCount with all prefix sums
        for (int i = 0; i < n - 1; i++) {
            rightCount[prefix[i]]++;
        }
        
        for (int i = 0; i < n; i++) {
            // Change nums[i] from original to k
            long long diff = k - nums[i];
            long long newTotal = total + diff;
            
            // Count partitions
            int count = 0;
            
            // Partitions in left side (before index i)
            if (i > 0) {
                long long target = newTotal / 2;
                count += leftCount[target];
            }
            
            // Partitions in right side (at or after index i)
            if (i < n - 1) {
                long long target = (newTotal - 2 * diff) / 2;
                count += rightCount[target];
            }
            
            result = max(result, count);
            
            // Update counts for next iteration
            if (i < n - 1) {
                rightCount[prefix[i]]--;
                if (rightCount[prefix[i]] == 0) {
                    rightCount.erase(prefix[i]);
                }
                if (i > 0) {
                    leftCount[prefix[i - 1]]++;
                }
            }
        }
        
        return result;
    }
};