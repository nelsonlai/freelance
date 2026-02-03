/*
 * Problem: Split Array into Consecutive Subsequences
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort, queue, heap
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
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> count, end;
        
        for (int num : nums) {
            count[num]++;
        }
        
        for (int num : nums) {
            if (count[num] == 0) {
                continue;
            }
            
            count[num]--;
            
            if (end[num - 1] > 0) {
                end[num - 1]--;
                end[num]++;
            } else if (count[num + 1] > 0 && count[num + 2] > 0) {
                count[num + 1]--;
                count[num + 2]--;
                end[num + 2]++;
            } else {
                return false;
            }
        }
        
        return true;
    }
};