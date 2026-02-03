/**
 * Problem: Contains Duplicate III
 * Difficulty: Hard
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean containsNearbyAlmostDuplicate(int[] nums, int indexDiff, int valueDiff) {
        if (valueDiff < 0) {
            return false;
        }
        
        Map<Long, Long> buckets = new HashMap<>();
        long bucketSize = (long) valueDiff + 1;
        
        for (int i = 0; i < nums.length; i++) {
            long num = nums[i];
            long bucketId = num >= 0 ? num / bucketSize : (num + 1) / bucketSize - 1;
            
            if (buckets.containsKey(bucketId)) {
                return true;
            }
            
            if (buckets.containsKey(bucketId - 1) && Math.abs(num - buckets.get(bucketId - 1)) <= valueDiff) {
                return true;
            }
            
            if (buckets.containsKey(bucketId + 1) && Math.abs(num - buckets.get(bucketId + 1)) <= valueDiff) {
                return true;
            }
            
            buckets.put(bucketId, num);
            
            if (i >= indexDiff) {
                long oldNum = nums[i - indexDiff];
                long oldBucketId = oldNum >= 0 ? oldNum / bucketSize : (oldNum + 1) / bucketSize - 1;
                buckets.remove(oldBucketId);
            }
        }
        
        return false;
    }
}