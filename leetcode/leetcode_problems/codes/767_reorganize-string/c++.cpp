#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        priority_queue<pair<int, char>> heap;
        for (auto& entry : count) {
            heap.push({entry.second, entry.first});
        }
        
        string result = "";
        pair<int, char> prev = {-1, ' '};
        
        while (!heap.empty() || prev.first != -1) {
            if (heap.empty() && prev.first != -1) {
                return "";
            }
            
            auto [freq, char] = heap.top();
            heap.pop();
            result += char;
            freq--;
            
            if (prev.first != -1) {
                heap.push(prev);
                prev = {-1, ' '};
            }
            
            if (freq > 0) {
                prev = {freq, char};
            }
        }
        
        return result;
    }
};
