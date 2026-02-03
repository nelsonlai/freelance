#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> A, B;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1) {
                    A.push_back({i, j});
                }
                if (img2[i][j] == 1) {
                    B.push_back({i, j});
                }
            }
        }
        
        unordered_map<string, int> count;
        for (auto& a : A) {
            for (auto& b : B) {
                string key = to_string(a.first - b.first) + "," + to_string(a.second - b.second);
                count[key]++;
            }
        }
        
        int result = 0;
        for (auto& entry : count) {
            result = max(result, entry.second);
        }
        return result;
    }
};
