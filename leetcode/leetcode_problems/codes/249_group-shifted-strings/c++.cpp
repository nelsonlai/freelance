/*
 * Problem: Group Shifted Strings
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    string getKey(string s) {
        if (s.empty()) {
            return "";
        }
        string key;
        int base = s[0] - 'a';
        for (char c : s) {
            int diff = (c - 'a' - base + 26) % 26;
            key += to_string(diff) + ",";
        }
        return key;
    }

public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> groups;
        
        for (string s : strings) {
            groups[getKey(s)].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
};