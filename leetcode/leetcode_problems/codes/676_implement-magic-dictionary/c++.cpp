/*
 * Problem: Implement Magic Dictionary
 * Difficulty: Medium
 * Tags: array, string, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class MagicDictionary {
private:
    unordered_set<string> words;
    unordered_map<string, int> count;

public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        words.clear();
        count.clear();
        
        for (string word : dictionary) {
            words.insert(word);
            for (int i = 0; i < word.length(); i++) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
                count[pattern]++;
            }
        }
    }
    
    bool search(string searchWord) {
        for (int i = 0; i < searchWord.length(); i++) {
            string pattern = searchWord.substr(0, i) + "*" + searchWord.substr(i + 1);
            if (count.find(pattern) != count.end()) {
                if (words.find(searchWord) == words.end() || count[pattern] > 1) {
                    return true;
                }
            }
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */