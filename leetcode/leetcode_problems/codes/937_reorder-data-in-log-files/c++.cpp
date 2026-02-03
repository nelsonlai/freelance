/*
 * Problem: Reorder Data in Log Files
 * Difficulty: Medium
 * Tags: array, string, graph, sort
 * 
 * Approach: Separate letter logs and digit logs, sort letter logs by content then identifier
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for separating logs
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> letterLogs, digitLogs;
        
        for (string& log : logs) {
            int spaceIdx = log.find(' ');
            string content = log.substr(spaceIdx + 1);
            if (isdigit(content[0])) {
                digitLogs.push_back(log);
            } else {
                letterLogs.push_back(log);
            }
        }
        
        sort(letterLogs.begin(), letterLogs.end(), [](const string& a, const string& b) {
            int spaceIdxA = a.find(' ');
            int spaceIdxB = b.find(' ');
            string contentA = a.substr(spaceIdxA + 1);
            string contentB = b.substr(spaceIdxB + 1);
            if (contentA != contentB) {
                return contentA < contentB;
            }
            return a.substr(0, spaceIdxA) < b.substr(0, spaceIdxB);
        });
        
        letterLogs.insert(letterLogs.end(), digitLogs.begin(), digitLogs.end());
        return letterLogs;
    }
};