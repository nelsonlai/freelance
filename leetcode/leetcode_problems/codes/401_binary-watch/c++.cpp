/*
 * Problem: Binary Watch
 * Difficulty: Easy
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <bitset>

using namespace std;

class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        
        for (int hour = 0; hour < 12; hour++) {
            for (int minute = 0; minute < 60; minute++) {
                if (bitset<10>(hour).count() + bitset<10>(minute).count() == turnedOn) {
                    result.push_back(to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute));
                }
            }
        }
        
        return result;
    }
};