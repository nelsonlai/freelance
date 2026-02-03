/*
 * Problem: The Number of Weak Characters in the Game
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort by attack descending, defense ascending, track max defense
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        sort(properties.begin(), properties.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] > b[0];  // Descending by attack
            }
            return a[1] < b[1];  // Ascending by defense
        });
        
        int count = 0;
        int maxDefense = 0;
        
        for (auto& prop : properties) {
            if (prop[1] < maxDefense) {
                count++;
            }
            maxDefense = max(maxDefense, prop[1]);
        }
        
        return count;
    }
};