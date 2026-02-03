/*
 * Problem: Squirrel Simulation
 * Difficulty: Medium
 * Tags: array, tree, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {
        int total = 0;
        int maxDiff = INT_MIN;
        
        for (auto& nut : nuts) {
            int distToTree = abs(nut[0] - tree[0]) + abs(nut[1] - tree[1]);
            int distToSquirrel = abs(nut[0] - squirrel[0]) + abs(nut[1] - squirrel[1]);
            total += distToTree * 2;
            maxDiff = max(maxDiff, distToTree - distToSquirrel);
        }
        
        return total - maxDiff;
    }
};