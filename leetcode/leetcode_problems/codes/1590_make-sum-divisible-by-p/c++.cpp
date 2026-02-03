/*
 * Problem: Make Sum Divisible by P
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;
        for (int num : nums) {
            total += num;
        }
        int remainder = (int)(total % p);
        if (remainder == 0) {
            return 0;
        }
        
        unordered_map<int, int> lastPos;
        lastPos[0] = -1;
        long long prefix = 0;
        int result = nums.size();
        
        for (int i = 0; i < nums.size(); i++) {
            prefix = (prefix + nums[i]) % p;
            int target = (int)((prefix - remainder + p) % p);
            
            if (lastPos.find(target) != lastPos.end()) {
                result = min(result, i - lastPos[target]);
            }
            
            lastPos[(int)prefix] = i;
        }
        
        return result < (int)nums.size() ? result : -1;
    }
};