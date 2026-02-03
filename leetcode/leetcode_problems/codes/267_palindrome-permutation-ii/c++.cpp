/*
 * Problem: Palindrome Permutation II
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
private:
    void permute(vector<char>& chars, int start, string mid, vector<string>& result) {
        if (start == chars.size()) {
            string first(chars.begin(), chars.end());
            string second = first;
            reverse(second.begin(), second.end());
            result.push_back(first + mid + second);
            return;
        }
        
        set<char> seen;
        for (int i = start; i < chars.size(); i++) {
            if (seen.find(chars[i]) == seen.end()) {
                seen.insert(chars[i]);
                swap(chars[start], chars[i]);
                permute(chars, start + 1, mid, result);
                swap(chars[start], chars[i]);
            }
        }
    }

public:
    vector<string> generatePalindromes(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        vector<char> oddChars;
        for (auto& pair : count) {
            if (pair.second % 2 == 1) {
                oddChars.push_back(pair.first);
            }
        }
        
        if (oddChars.size() > 1) {
            return {};
        }
        
        string mid = oddChars.empty() ? "" : string(1, oddChars[0]);
        vector<char> half;
        for (auto& pair : count) {
            for (int i = 0; i < pair.second / 2; i++) {
                half.push_back(pair.first);
            }
        }
        
        vector<string> result;
        permute(half, 0, mid, result);
        return result;
    }
};