/*
 * Problem: Eliminate Maximum Number of Monsters
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort by arrival time, eliminate one per minute
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();
        vector<double> arrivalTimes(n);
        for (int i = 0; i < n; i++) {
            arrivalTimes[i] = (double) dist[i] / speed[i];
        }
        sort(arrivalTimes.begin(), arrivalTimes.end());
        
        for (int i = 0; i < n; i++) {
            if (arrivalTimes[i] <= i) {
                return i;
            }
        }
        
        return n;
    }
};