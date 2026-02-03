/*
 * Problem: Intersection of Two Arrays II
 * Difficulty: Easy
 * Tags: array, hash, sort, search
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
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> count;
        for (int num : nums1) {
            count[num]++;
        }
        
        vector<int> result;
        for (int num : nums2) {
            if (count[num] > 0) {
                result.push_back(num);
                count[num]--;
            }
        }
        
        return result;
    }
};