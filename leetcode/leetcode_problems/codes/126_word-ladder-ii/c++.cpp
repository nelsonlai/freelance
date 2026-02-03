/*
 * Problem: Word Ladder II
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
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
private:
    void backtrack(const string& word, const string& beginWord, vector<string>& path,
                   unordered_map<string, vector<string>>& parents, vector<vector<string>>& result) {
        path.push_back(word);
        if (word == beginWord) {
            vector<string> solution = path;
            reverse(solution.begin(), solution.end());
            result.push_back(solution);
        } else {
            for (const string& parent : parents[word]) {
                backtrack(parent, beginWord, path, parents, result);
            }
        }
        path.pop_back();
    }
    
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) {
            return result;
        }
        
        wordSet.insert(beginWord);
        unordered_map<string, vector<string>> neighbors;
        for (const string& word : wordSet) {
            for (int i = 0; i < word.length(); i++) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
                neighbors[pattern].push_back(word);
            }
        }
        
        unordered_map<string, int> distance;
        unordered_map<string, vector<string>> parents;
        queue<string> q;
        q.push(beginWord);
        distance[beginWord] = 0;
        bool found = false;
        
        while (!q.empty() && !found) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                for (int j = 0; j < word.length(); j++) {
                    string pattern = word.substr(0, j) + "*" + word.substr(j + 1);
                    for (const string& neighbor : neighbors[pattern]) {
                        if (distance.find(neighbor) == distance.end()) {
                            distance[neighbor] = distance[word] + 1;
                            parents[neighbor] = vector<string>();
                            parents[neighbor].push_back(word);
                            q.push(neighbor);
                        } else if (distance[neighbor] == distance[word] + 1) {
                            parents[neighbor].push_back(word);
                        }
                        if (neighbor == endWord) {
                            found = true;
                        }
                    }
                }
            }
        }
        
        if (found) {
            vector<string> path;
            backtrack(endWord, beginWord, path, parents, result);
        }
        
        return result;
    }
};