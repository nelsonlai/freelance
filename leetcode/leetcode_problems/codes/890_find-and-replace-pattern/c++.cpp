#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    bool match(string& word, string& pattern) {
        unordered_map<char, char> m1, m2;
        for (int i = 0; i < word.length(); i++) {
            char w = word[i];
            char p = pattern[i];
            if (m1.find(w) == m1.end()) {
                m1[w] = p;
            }
            if (m2.find(p) == m2.end()) {
                m2[p] = w;
            }
            if (m1[w] != p || m2[p] != w) {
                return false;
            }
        }
        return true;
    }

public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> result;
        for (string word : words) {
            if (match(word, pattern)) {
                result.push_back(word);
            }
        }
        return result;
    }
};
