/*
 * Problem: Split Concatenated Strings
 * Difficulty: Medium
 * Tags: array, string, graph, greedy
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
    string splitLoopedString(vector<string>& strs) {
        vector<string> optimized;
        for (string s : strs) {
            string reversed = s;
            reverse(reversed.begin(), reversed.end());
            optimized.push_back(s > reversed ? s : reversed);
        }
        
        string result = "";
        for (string s : optimized) {
            result += s;
        }
        
        for (int i = 0; i < strs.size(); i++) {
            vector<string> candidates = {strs[i], strs[i]};
            reverse(candidates[1].begin(), candidates[1].end());
            for (string start : candidates) {
                for (int j = 0; j < start.length(); j++) {
                    string candidate = start.substr(j);
                    for (int k = i + 1; k < strs.size(); k++) {
                        candidate += optimized[k];
                    }
                    for (int k = 0; k < i; k++) {
                        candidate += optimized[k];
                    }
                    candidate += start.substr(0, j);
                    if (candidate > result) {
                        result = candidate;
                    }
                }
            }
        }
        
        return result;
    }
};