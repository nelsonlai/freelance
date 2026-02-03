/*
 * Problem: Build an Array With Stack Operations
 * Difficulty: Medium
 * Tags: array, stack
 * 
 * Approach: Simulate - push numbers 1 to n, pop if not in target
 * Time Complexity: O(n) where n is max number
 * Space Complexity: O(n) for result
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        unordered_set<int> targetSet(target.begin(), target.end());
        
        vector<string> result;
        int targetIdx = 0;
        
        for (int i = 1; i <= n && targetIdx < target.size(); i++) {
            result.push_back("Push");
            if (targetSet.find(i) == targetSet.end()) {
                result.push_back("Pop");
            } else {
                targetIdx++;
            }
        }
        
        return result;
    }
};