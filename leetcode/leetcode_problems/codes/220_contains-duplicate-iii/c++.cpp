/*
 * Problem: Contains Duplicate III
 * Difficulty: Hard
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (valueDiff < 0) {
            return false;
        }
        
        unordered_map<long, long> buckets;
        long bucketSize = (long)valueDiff + 1;
        
        for (int i = 0; i < nums.size(); i++) {
            long num = nums[i];
            long bucketId = num >= 0 ? num / bucketSize : (num + 1) / bucketSize - 1;
            
            if (buckets.find(bucketId) != buckets.end()) {
                return true;
            }
            
            if (buckets.find(bucketId - 1) != buckets.end() && abs(num - buckets[bucketId - 1]) <= valueDiff) {
                return true;
            }
            
            if (buckets.find(bucketId + 1) != buckets.end() && abs(num - buckets[bucketId + 1]) <= valueDiff) {
                return true;
            }
            
            buckets[bucketId] = num;
            
            if (i >= indexDiff) {
                long oldNum = nums[i - indexDiff];
                long oldBucketId = oldNum >= 0 ? oldNum / bucketSize : (oldNum + 1) / bucketSize - 1;
                buckets.erase(oldBucketId);
            }
        }
        
        return false;
    }
};