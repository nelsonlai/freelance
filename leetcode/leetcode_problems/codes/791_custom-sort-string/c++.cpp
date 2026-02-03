#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string customSortString(string order, string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        string result = "";
        for (char c : order) {
            result += string(count[c], c);
            count[c] = 0;
        }
        
        for (auto& entry : count) {
            result += string(entry.second, entry.first);
        }
        
        return result;
    }
};
