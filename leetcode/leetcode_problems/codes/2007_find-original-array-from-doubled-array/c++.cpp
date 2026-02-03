/*
 * Problem: Find Original Array From Doubled Array
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort
 * 
 * Approach: Sort and use greedy - match each number with its double
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        if (changed.size() % 2 != 0) {
            return {};
        }
        
        unordered_map<int, int> count;
        for (int num : changed) {
            count[num]++;
        }
        
        sort(changed.begin(), changed.end());
        vector<int> result;
        
        for (int num : changed) {
            if (count[num] == 0) {
                continue;
            }
            
            int doubleVal = num * 2;
            if (count[doubleVal] == 0) {
                return {};
            }
            
            count[num]--;
            count[doubleVal]--;
            result.push_back(num);
        }
        
        return result;
    }
};