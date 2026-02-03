/*
 * Problem: Restore IP Addresses
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> path;
        backtrack(result, path, s, 0);
        return result;
    }
    
private:
    void backtrack(vector<string>& result, vector<string>& path, string& s, int start) {
        if (path.size() == 4) {
            if (start == s.length()) {
                string ip = path[0];
                for (int i = 1; i < 4; i++) {
                    ip += "." + path[i];
                }
                result.push_back(ip);
            }
            return;
        }
        
        for (int i = start; i < min(start + 3, (int)s.length()); i++) {
            string segment = s.substr(start, i - start + 1);
            if ((segment.length() > 1 && segment[0] == '0') || stoi(segment) > 255) {
                continue;
            }
            path.push_back(segment);
            backtrack(result, path, s, i + 1);
            path.pop_back();
        }
    }
};