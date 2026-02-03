/*
 * Problem: 4Sum II
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
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> sumCount;
        for (int a : nums1) {
            for (int b : nums2) {
                sumCount[a + b]++;
            }
        }
        
        int count = 0;
        for (int c : nums3) {
            for (int d : nums4) {
                count += sumCount[-(c + d)];
            }
        }
        
        return count;
    }
};