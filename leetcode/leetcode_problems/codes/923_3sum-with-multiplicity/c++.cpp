#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        int MOD = 1000000007;
        unordered_map<int, long> count;
        for (int num : arr) {
            count[num]++;
        }
        
        vector<int> keys;
        for (auto& pair : count) {
            keys.push_back(pair.first);
        }
        sort(keys.begin(), keys.end());
        
        long result = 0;
        for (int i = 0; i < keys.size(); i++) {
            int x = keys[i];
            for (int j = i; j < keys.size(); j++) {
                int y = keys[j];
                int z = target - x - y;
                if (z < y) break;
                if (count.find(z) == count.end()) continue;
                
                if (x == y && y == z) {
                    long cnt = count[x];
                    result += cnt * (cnt - 1) * (cnt - 2) / 6;
                } else if (x == y) {
                    long cnt = count[x];
                    result += cnt * (cnt - 1) / 2 * count[z];
                } else if (y == z) {
                    result += count[x] * count[y] * (count[y] - 1) / 2;
                } else {
                    result += count[x] * count[y] * count[z];
                }
            }
        }
        
        return (int)(result % MOD);
    }
};
