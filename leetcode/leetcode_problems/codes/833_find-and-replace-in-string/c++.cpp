#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        vector<pair<int, int>> sorted;
        for (int i = 0; i < indices.size(); i++) {
            sorted.push_back({indices[i], i});
        }
        sort(sorted.rbegin(), sorted.rend());
        
        for (auto& item : sorted) {
            int idx = item.first;
            int i = item.second;
            if (s.substr(idx, sources[i].length()) == sources[i]) {
                s = s.substr(0, idx) + targets[i] + s.substr(idx + sources[i].length());
            }
        }
        return s;
    }
};
