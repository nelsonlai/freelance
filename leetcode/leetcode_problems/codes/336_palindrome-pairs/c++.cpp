/*
 * Problem: Palindrome Pairs
 * Difficulty: Hard
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordMap;
        for (int i = 0; i < words.size(); i++) {
            wordMap[words[i]] = i;
        }
        
        vector<vector<int>> result;
        
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            for (int j = 0; j <= word.length(); j++) {
                string prefix = word.substr(0, j);
                string suffix = word.substr(j);
                
                if (isPalindrome(prefix)) {
                    string revSuffix = suffix;
                    reverse(revSuffix.begin(), revSuffix.end());
                    if (wordMap.find(revSuffix) != wordMap.end() && wordMap[revSuffix] != i) {
                        result.push_back({wordMap[revSuffix], i});
                    }
                }
                
                if (j != word.length() && isPalindrome(suffix)) {
                    string revPrefix = prefix;
                    reverse(revPrefix.begin(), revPrefix.end());
                    if (wordMap.find(revPrefix) != wordMap.end() && wordMap[revPrefix] != i) {
                        result.push_back({i, wordMap[revPrefix]});
                    }
                }
            }
        }
        
        return result;
    }
};