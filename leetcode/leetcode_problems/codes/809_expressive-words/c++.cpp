#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<pair<char, int>> getGroups(string word) {
        vector<pair<char, int>> groups;
        int i = 0;
        while (i < word.length()) {
            int j = i;
            while (j < word.length() && word[j] == word[i]) {
                j++;
            }
            groups.push_back({word[i], j - i});
            i = j;
        }
        return groups;
    }

public:
    int expressiveWords(string s, vector<string>& words) {
        auto sGroups = getGroups(s);
        int result = 0;
        
        for (string word : words) {
            auto wGroups = getGroups(word);
            if (sGroups.size() != wGroups.size()) {
                continue;
            }
            bool valid = true;
            for (int i = 0; i < sGroups.size(); i++) {
                if (sGroups[i].first != wGroups[i].first) {
                    valid = false;
                    break;
                }
                if (sGroups[i].second < wGroups[i].second || 
                    (sGroups[i].second < 3 && sGroups[i].second != wGroups[i].second)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result++;
            }
        }
        return result;
    }
};
