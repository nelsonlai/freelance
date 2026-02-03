/*
 * Problem: Largest Number
 * Difficulty: Medium
 * Tags: array, string, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> numStrings;
        for (int num : nums) {
            numStrings.push_back(to_string(num));
        }
        
        sort(numStrings.begin(), numStrings.end(), [](const string& a, const string& b) {
            return (b + a) < (a + b);
        });
        
        if (numStrings[0] == "0") {
            return "0";
        }
        
        string result;
        for (const string& num : numStrings) {
            result += num;
        }
        
        return result;
    }
};