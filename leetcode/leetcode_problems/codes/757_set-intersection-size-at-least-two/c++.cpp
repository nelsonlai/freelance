#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
        });
        
        vector<int> result;
        for (auto& interval : intervals) {
            int start = interval[0], end = interval[1];
            int count = 0;
            for (int x : result) {
                if (start <= x && x <= end) {
                    count++;
                }
            }
            if (count == 0) {
                result.push_back(end - 1);
                result.push_back(end);
            } else if (count == 1) {
                result.push_back(end);
            }
        }
        
        return result.size();
    }
};
