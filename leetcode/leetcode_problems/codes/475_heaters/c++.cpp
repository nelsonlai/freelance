/*
 * Problem: Heaters
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int radius = 0;
        int i = 0;
        
        for (int house : houses) {
            while (i < heaters.size() - 1 && 
                   abs(heaters[i+1] - house) <= abs(heaters[i] - house)) {
                i++;
            }
            radius = max(radius, abs(heaters[i] - house));
        }
        
        return radius;
    }
};