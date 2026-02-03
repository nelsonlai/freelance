/*
 * Problem: Maximum Number of People That Can Be Caught in Tag
 * Difficulty: Medium
 * Tags: array, greedy, two pointers
 * 
 * Approach: Two pointers - match taggers (1) with runners (0) within distance
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int catchMaximumAmountofPeople(vector<int>& team, int dist) {
        vector<int> taggers, runners;
        
        for (int i = 0; i < team.size(); i++) {
            if (team[i] == 1) {
                taggers.push_back(i);
            } else {
                runners.push_back(i);
            }
        }
        
        if (taggers.empty() || runners.empty()) {
            return 0;
        }
        
        int count = 0;
        int tIdx = 0, rIdx = 0;
        
        while (tIdx < taggers.size() && rIdx < runners.size()) {
            if (abs(taggers[tIdx] - runners[rIdx]) <= dist) {
                count++;
                tIdx++;
                rIdx++;
            } else if (taggers[tIdx] < runners[rIdx]) {
                tIdx++;
            } else {
                rIdx++;
            }
        }
        
        return count;
    }
};