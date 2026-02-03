#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> count;
        for (int ans : answers) {
            count[ans]++;
        }
        
        int result = 0;
        for (auto& entry : count) {
            int answer = entry.first;
            int freq = entry.second;
            result += (freq + answer) / (answer + 1) * (answer + 1);
        }
        return result;
    }
};
