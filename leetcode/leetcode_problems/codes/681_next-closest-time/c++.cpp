/*
 * Problem: Next Closest Time
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string nextClosestTime(string time) {
        set<char> digits;
        for (char c : time) {
            if (c != ':') {
                digits.insert(c);
            }
        }
        
        string timeStr = time;
        timeStr.erase(remove(timeStr.begin(), timeStr.end(), ':'), timeStr.end());
        
        for (int i = 3; i >= 0; i--) {
            for (char digit : digits) {
                if (digit > timeStr[i]) {
                    timeStr[i] = digit;
                    for (int j = i + 1; j < 4; j++) {
                        timeStr[j] = *digits.begin();
                    }
                    string candidate = timeStr.substr(0, 2) + ":" + timeStr.substr(2);
                    if (candidate.substr(0, 2) < "24" && candidate.substr(3) < "60") {
                        return candidate;
                    }
                }
            }
            timeStr[i] = *digits.begin();
        }
        
        char minDigit = *digits.begin();
        return string(2, minDigit) + ":" + string(2, minDigit);
    }
};