/*
 * Problem: Word Abbreviation
 * Difficulty: Hard
 * Tags: array, string, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    string getAbbrev(string word, int prefixLen) {
        if (word.length() <= prefixLen + 2) {
            return word;
        }
        return word.substr(0, prefixLen) + to_string(word.length() - prefixLen - 1) + word.back();
    }

public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size();
        vector<string> result(n);
        vector<int> prefixLen(n, 1);
        
        for (int i = 0; i < n; i++) {
            result[i] = getAbbrev(words[i], prefixLen[i]);
        }
        
        for (int i = 0; i < n; i++) {
            while (true) {
                vector<int> duplicates;
                for (int j = i + 1; j < n; j++) {
                    if (result[i] == result[j]) {
                        duplicates.push_back(j);
                    }
                }
                if (duplicates.empty()) {
                    break;
                }
                duplicates.push_back(i);
                for (int idx : duplicates) {
                    prefixLen[idx]++;
                    result[idx] = getAbbrev(words[idx], prefixLen[idx]);
                }
            }
        }
        
        return result;
    }
};