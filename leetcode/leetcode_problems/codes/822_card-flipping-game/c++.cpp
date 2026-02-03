#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        unordered_set<int> same;
        for (int i = 0; i < fronts.size(); i++) {
            if (fronts[i] == backs[i]) {
                same.insert(fronts[i]);
            }
        }
        
        int result = INT_MAX;
        for (int i = 0; i < fronts.size(); i++) {
            if (same.find(fronts[i]) == same.end()) {
                result = min(result, fronts[i]);
            }
            if (same.find(backs[i]) == same.end()) {
                result = min(result, backs[i]);
            }
        }
        
        return result == INT_MAX ? 0 : result;
    }
};
