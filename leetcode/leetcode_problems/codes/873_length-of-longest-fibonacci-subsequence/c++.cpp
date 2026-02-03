#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int, int> index;
        for (int i = 0; i < arr.size(); i++) {
            index[arr[i]] = i;
        }
        
        unordered_map<string, int> longest;
        int result = 0;
        
        for (int k = 0; k < arr.size(); k++) {
            for (int j = 0; j < k; j++) {
                int i = index.count(arr[k] - arr[j]) ? index[arr[k] - arr[j]] : -1;
                if (i >= 0 && i < j) {
                    string key = to_string(i) + "," + to_string(j);
                    int cand = (longest.count(key) ? longest[key] : 2) + 1;
                    longest[to_string(j) + "," + to_string(k)] = cand;
                    result = max(result, cand);
                }
            }
        }
        
        return result >= 3 ? result : 0;
    }
};
