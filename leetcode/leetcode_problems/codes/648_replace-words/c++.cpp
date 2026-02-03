/*
 * Problem: Replace Words
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());
        stringstream ss(sentence);
        string word;
        vector<string> words;
        
        while (ss >> word) {
            words.push_back(word);
        }
        
        for (int i = 0; i < words.size(); i++) {
            for (int j = 1; j <= words[i].length(); j++) {
                string prefix = words[i].substr(0, j);
                if (dictionarySet.find(prefix) != dictionarySet.end()) {
                    words[i] = prefix;
                    break;
                }
            }
        }
        
        string result = "";
        for (int i = 0; i < words.size(); i++) {
            if (i > 0) result += " ";
            result += words[i];
        }
        
        return result;
    }
};