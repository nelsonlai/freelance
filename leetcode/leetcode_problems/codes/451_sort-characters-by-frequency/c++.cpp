/*
 * Problem: Sort Characters By Frequency
 * Difficulty: Medium
 * Tags: string, tree, hash, sort, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        vector<pair<char, int>> vec(count.begin(), count.end());
        sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
            return a.second > b.second;
        });
        
        string result = "";
        for (auto& entry : vec) {
            for (int i = 0; i < entry.second; i++) {
                result += entry.first;
            }
        }
        
        return result;
    }
};