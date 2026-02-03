/*
 * Problem: Self Crossing
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        if (distance.size() < 4) {
            return false;
        }
        
        for (int i = 3; i < distance.size(); i++) {
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                return true;
            }
            if (i >= 4 && distance[i - 1] == distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
            if (i >= 5 && distance[i - 2] >= distance[i - 4] && 
                distance[i - 1] <= distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2] && 
                distance[i - 1] + distance[i - 5] >= distance[i - 3]) {
                return true;
            }
        }
        
        return false;
    }
};