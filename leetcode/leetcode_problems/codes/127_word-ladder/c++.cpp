/*
 * Problem: Word Ladder
 * Difficulty: Hard
 * Tags: string, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        queue<string> q;
        q.push(beginWord);
        int length = 1;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                if (word == endWord) {
                    return length;
                }
                
                for (int j = 0; j < word.length(); j++) {
                    char original = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        word[j] = c;
                        if (wordSet.find(word) != wordSet.end()) {
                            wordSet.erase(word);
                            q.push(word);
                        }
                    }
                    word[j] = original;
                }
            }
            length++;
        }
        
        return 0;
    }
};