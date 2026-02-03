#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.length() != goal.length()) {
            return false;
        }
        
        if (s == goal) {
            unordered_set<char> set(s.begin(), s.end());
            return set.size() < s.length();
        }
        
        vector<pair<char, char>> diff;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != goal[i]) {
                diff.push_back({s[i], goal[i]});
            }
        }
        return diff.size() == 2 && diff[0].first == diff[1].second && diff[0].second == diff[1].first;
    }
};
