/*
 * Problem: Construct the Rectangle
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        int w = (int)sqrt(area);
        while (area % w != 0) {
            w--;
        }
        return {area / w, w};
    }
};