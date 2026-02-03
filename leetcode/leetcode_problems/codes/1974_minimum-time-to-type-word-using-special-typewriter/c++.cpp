/*
 * Problem: Minimum Time to Type Word Using Special Typewriter
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Calculate min distance between consecutive characters (clockwise or counterclockwise)
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTimeToType(string word) {
        int time = 0;
        char current = 'a';
        
        for (char c : word) {
            int diff = abs(c - current);
            time += min(diff, 26 - diff) + 1;  // +1 for typing
            current = c;
        }
        
        return time;
    }
};