/*
 * Problem: Two Out of Three
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Count occurrences in each array, return numbers appearing in at least 2 arrays
 * Time Complexity: O(n) where n is total elements
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        unordered_map<int, unordered_set<int>> count;
        
        for (int num : nums1) {
            count[num].insert(1);
        }
        for (int num : nums2) {
            count[num].insert(2);
        }
        for (int num : nums3) {
            count[num].insert(3);
        }
        
        vector<int> result;
        for (auto& [num, arrays] : count) {
            if (arrays.size() >= 2) {
                result.push_back(num);
            }
        }
        
        return result;
    }
};