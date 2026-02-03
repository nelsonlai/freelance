/*
 * Problem: Intersection of Two Arrays
 * Difficulty: Easy
 * Tags: array, hash, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> resultSet;
        
        for (int num : nums2) {
            if (set1.find(num) != set1.end()) {
                resultSet.insert(num);
            }
        }
        
        return vector<int>(resultSet.begin(), resultSet.end());
    }
};