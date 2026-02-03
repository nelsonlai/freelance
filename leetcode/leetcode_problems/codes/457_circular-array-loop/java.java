/**
 * Problem: Circular Array Loop
 * Difficulty: Medium
 * Tags: array, graph, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

class Solution {
    public boolean circularArrayLoop(int[] nums) {
        int n = nums.length;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }
            
            int slow = i, fast = i;
            boolean direction = nums[i] > 0;
            
            while (true) {
                slow = getNext(nums, slow);
                fast = getNext(nums, getNext(nums, fast));
                
                if ((nums[slow] > 0) != direction || (nums[fast] > 0) != direction) {
                    break;
                }
                
                if (slow == fast) {
                    if (slow == getNext(nums, slow)) {
                        break;
                    }
                    return true;
                }
            }
            
            int visited = i;
            while ((nums[visited] > 0) == direction) {
                int next = getNext(nums, visited);
                nums[visited] = 0;
                visited = next;
            }
        }
        
        return false;
    }
    
    private int getNext(int[] nums, int i) {
        int n = nums.length;
        return ((i + nums[i]) % n + n) % n;
    }
}