#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> maxCount(26, 0);
        for (string word : words2) {
            vector<int> count = getCount(word);
            for (int i = 0; i < 26; i++) {
                maxCount[i] = max(maxCount[i], count[i]);
            }
        }
        
        vector<string> result;
        for (string word : words1) {
            vector<int> count = getCount(word);
            bool valid = true;
            for (int i = 0; i < 26; i++) {
                if (count[i] < maxCount[i]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result.push_back(word);
            }
        }
        
        return result;
    }
    
private:
    vector<int> getCount(string word) {
        vector<int> count(26, 0);
        for (char c : word) {
            count[c - 'a']++;
        }
        return count;
    }
};
