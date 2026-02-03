#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int kSimilarity(string s1, string s2) {
        if (s1 == s2) {
            return 0;
        }
        
        queue<pair<string, int>> q;
        q.push({s1, 0});
        unordered_set<string> visited;
        visited.insert(s1);
        
        while (!q.empty()) {
            auto [s, steps] = q.front();
            q.pop();
            
            if (s == s2) {
                return steps;
            }
            
            int i = 0;
            while (i < s.length() && s[i] == s2[i]) {
                i++;
            }
            
            for (int j = i + 1; j < s.length(); j++) {
                if (s[j] == s2[i] && s[j] != s2[j]) {
                    string newS = s.substr(0, i) + s[j] + s.substr(i + 1, j - i - 1) + s[i] + s.substr(j + 1);
                    if (visited.find(newS) == visited.end()) {
                        visited.insert(newS);
                        q.push({newS, steps + 1});
                    }
                }
            }
        }
        return -1;
    }
};
