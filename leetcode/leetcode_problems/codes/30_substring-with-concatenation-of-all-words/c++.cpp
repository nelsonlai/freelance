/*
 * Problem: Substring with Concatenation of All Words
 * Difficulty: Hard
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) {
            return result;
        }
        
        int wordLen = words[0].length();
        int totalLen = words.size() * wordLen;
        unordered_map<string, int> wordCount;
        for (const string& word : words) {
            wordCount[word]++;
        }
        
        for (int i = 0; i < wordLen; i++) {
            int left = i;
            unordered_map<string, int> seen;
            int count = 0;
            
            for (int j = i; j <= (int)s.length() - wordLen; j += wordLen) {
                string word = s.substr(j, wordLen);
                
                if (wordCount.find(word) != wordCount.end()) {
                    seen[word]++;
                    count++;
                    
                    while (seen[word] > wordCount[word]) {
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                    
                    if (count == words.size()) {
                        result.push_back(left);
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                } else {
                    seen.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
    }
};