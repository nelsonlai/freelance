/*
 * Problem: Making File Names Unique
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_set<string> used;
        vector<string> result;
        
        for (string name : names) {
            if (used.find(name) == used.end()) {
                result.push_back(name);
                used.insert(name);
            } else {
                int k = 1;
                string newName;
                do {
                    newName = name + "(" + to_string(k) + ")";
                    k++;
                } while (used.find(newName) != used.end());
                result.push_back(newName);
                used.insert(newName);
            }
        }
        
        return result;
    }
};