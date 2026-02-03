/*
 * Problem: Maximum Population Year
 * Difficulty: Easy
 * Tags: array, prefix sum
 * 
 * Approach: Use difference array to track population changes
 * Time Complexity: O(n) where n is logs
 * Space Complexity: O(1) - fixed size array
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> years(101, 0);
        
        for (auto& log : logs) {
            int birth = log[0];
            int death = log[1];
            years[birth - 1950]++;
            if (death - 1950 < 100) {
                years[death - 1950]--;
            }
        }
        
        int maxPop = 0;
        int maxYear = 1950;
        int currentPop = 0;
        
        for (int i = 0; i < 101; i++) {
            currentPop += years[i];
            if (currentPop > maxPop) {
                maxPop = currentPop;
                maxYear = 1950 + i;
            }
        }
        
        return maxYear;
    }
};