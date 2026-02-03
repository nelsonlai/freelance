#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        unordered_map<char, vector<pair<int, int>>> waiting;
        for (int i = 0; i < words.size(); i++) {
            waiting[words[i][0]].push_back({i, 0});
        }
        
        int result = 0;
        for (char c : s) {
            auto old = waiting[c];
            waiting[c].clear();
            for (auto& p : old) {
                int wordIdx = p.first;
                int charIdx = p.second + 1;
                if (charIdx < words[wordIdx].length()) {
                    waiting[words[wordIdx][charIdx]].push_back({wordIdx, charIdx});
                } else {
                    result++;
                }
            }
        }
        return result;
    }
};
