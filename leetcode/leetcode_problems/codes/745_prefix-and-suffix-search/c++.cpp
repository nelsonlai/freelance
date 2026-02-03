#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class WordFilter {
private:
    unordered_map<string, vector<int>> prefix;
    unordered_map<string, vector<int>> suffix;

public:
    WordFilter(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            for (int j = 0; j <= word.length(); j++) {
                string pre = word.substr(0, j);
                string suf = word.substr(j);
                prefix[pre].push_back(i);
                suffix[suf].push_back(i);
            }
        }
    }
    
    int f(string pref, string suff) {
        if (prefix.find(pref) == prefix.end() || suffix.find(suff) == suffix.end()) {
            return -1;
        }
        unordered_set<int> prefixSet(prefix[pref].begin(), prefix[pref].end());
        unordered_set<int> suffixSet(suffix[suff].begin(), suffix[suff].end());
        int result = -1;
        for (int idx : prefixSet) {
            if (suffixSet.find(idx) != suffixSet.end()) {
                result = max(result, idx);
            }
        }
        return result;
    }
};
