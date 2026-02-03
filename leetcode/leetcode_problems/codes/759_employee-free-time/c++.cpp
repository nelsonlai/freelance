#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>> schedule) {
        vector<Interval*> intervals;
        for (auto& emp : schedule) {
            intervals.insert(intervals.end(), emp.begin(), emp.end());
        }
        
        sort(intervals.begin(), intervals.end(), [](Interval* a, Interval* b) {
            return a->start < b->start;
        });
        
        vector<Interval*> merged;
        for (Interval* interval : intervals) {
            if (merged.empty() || merged.back()->end < interval->start) {
                merged.push_back(interval);
            } else {
                merged.back()->end = max(merged.back()->end, interval->end);
            }
        }
        
        vector<Interval*> result;
        for (int i = 0; i < merged.size() - 1; i++) {
            result.push_back(new Interval(merged[i]->end, merged[i + 1]->start));
        }
        
        return result;
    }
};
