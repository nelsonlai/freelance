/*
 * Problem: Find Duplicate File in System
 * Difficulty: Medium
 * Tags: array, string, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> contentMap;
        
        for (string path : paths) {
            stringstream ss(path);
            string segment;
            vector<string> parts;
            while (ss >> segment) {
                parts.push_back(segment);
            }
            
            string directory = parts[0];
            for (int i = 1; i < parts.size(); i++) {
                string fileInfo = parts[i];
                size_t pos = fileInfo.find('(');
                string name = fileInfo.substr(0, pos);
                string content = fileInfo.substr(pos + 1, fileInfo.length() - pos - 2);
                string fullPath = directory + "/" + name;
                contentMap[content].push_back(fullPath);
            }
        }
        
        vector<vector<string>> result;
        for (auto& entry : contentMap) {
            if (entry.second.size() > 1) {
                result.push_back(entry.second);
            }
        }
        
        return result;
    }
};