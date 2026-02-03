/*
 * Problem: Unique Word Abbreviation
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
#include <unordered_set>

using namespace std;

class ValidWordAbbr {
private:
    unordered_map<string, unordered_set<string>> abbrMap;
    
    string getAbbr(string word) {
        if (word.length() <= 2) {
            return word;
        }
        return word[0] + to_string(word.length() - 2) + word.back();
    }

public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (string word : dictionary) {
            abbrMap[getAbbr(word)].insert(word);
        }
    }
    
    bool isUnique(string word) {
        string abbr = getAbbr(word);
        if (abbrMap.find(abbr) == abbrMap.end()) {
            return true;
        }
        unordered_set<string>& words = abbrMap[abbr];
        return words.size() == 1 && words.find(word) != words.end();
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */