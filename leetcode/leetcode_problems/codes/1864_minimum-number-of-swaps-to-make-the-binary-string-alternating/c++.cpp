/*
 * Problem: Minimum Number of Swaps to Make the Binary String Alternating
 * Difficulty: Medium
 * Tags: string, greedy
 * 
 * Approach: Try both patterns (0-start, 1-start), count mismatches
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int countMismatches(const string& s, const string& pattern) {
        int mismatches = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != pattern[i % 2]) {
                mismatches++;
            }
        }
        return mismatches / 2;
    }
    
public:
    int minSwaps(string s) {
        int count0 = count(s.begin(), s.end(), '0');
        int count1 = s.length() - count0;
        
        if (abs(count0 - count1) > 1) {
            return -1;
        }
        
        if (count0 == count1) {
            return min(countMismatches(s, "01"), countMismatches(s, "10"));
        } else if (count0 > count1) {
            return countMismatches(s, "01");
        } else {
            return countMismatches(s, "10");
        }
    }
};