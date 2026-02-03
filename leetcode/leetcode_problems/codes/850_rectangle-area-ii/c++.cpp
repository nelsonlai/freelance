#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    long query(vector<pair<int, int>>& active) {
        long result = 0;
        int cur = -1;
        for (auto& interval : active) {
            cur = max(cur, interval.first);
            result += max(0, interval.second - cur);
            cur = max(cur, interval.second);
        }
        return result;
    }

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int MOD = 1000000007;
        vector<vector<int>> events;
        for (auto& rect : rectangles) {
            events.push_back({rect[1], 1, rect[0], rect[2]});
            events.push_back({rect[3], -1, rect[0], rect[2]});
        }
        sort(events.begin(), events.end());
        
        vector<pair<int, int>> active;
        long result = 0;
        int curY = events[0][0];
        
        for (auto& event : events) {
            int y = event[0], typ = event[1], x1 = event[2], x2 = event[3];
            result += query(active) * (y - curY);
            curY = y;
            
            if (typ == 1) {
                active.push_back({x1, x2});
                sort(active.begin(), active.end());
            } else {
                for (auto it = active.begin(); it != active.end(); it++) {
                    if (it->first == x1 && it->second == x2) {
                        active.erase(it);
                        break;
                    }
                }
            }
        }
        
        return (int)(result % MOD);
    }
};
