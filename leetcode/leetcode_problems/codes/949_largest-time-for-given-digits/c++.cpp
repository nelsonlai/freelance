/*
 * Problem: Largest Time for Given Digits
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Try all permutations and find valid time with maximum value
 * Time Complexity: O(4!) = O(24)
 * Space Complexity: O(1)
 */

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        int maxTime = -1;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (j == i) continue;
                for (int k = 0; k < 4; k++) {
                    if (k == i || k == j) continue;
                    int l = 6 - i - j - k;
                    
                    int hours = arr[i] * 10 + arr[j];
                    int minutes = arr[k] * 10 + arr[l];
                    
                    if (hours < 24 && minutes < 60) {
                        int timeValue = hours * 60 + minutes;
                        maxTime = max(maxTime, timeValue);
                    }
                }
            }
        }
        
        if (maxTime == -1) {
            return "";
        }
        
        int hours = maxTime / 60;
        int minutes = maxTime % 60;
        stringstream ss;
        ss << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes;
        return ss.str();
    }
};