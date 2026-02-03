/*
 * Problem: Data Stream as Disjoint Intervals
 * Difficulty: Hard
 * Tags: graph, hash, sort, search
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <algorithm>

using namespace std;

class SummaryRanges {
private:
    vector<vector<int>> intervals;

public:
    SummaryRanges() {
        
    }
    
    void addNum(int value) {
        vector<int> newInterval = {value, value};
        bool inserted = false;
        vector<vector<int>> newIntervals;
        
        for (auto& interval : intervals) {
            if (interval[1] < value - 1) {
                newIntervals.push_back(interval);
            } else if (interval[0] > value + 1) {
                if (!inserted) {
                    newIntervals.push_back(newInterval);
                    inserted = true;
                }
                newIntervals.push_back(interval);
            } else {
                newInterval[0] = min(newInterval[0], interval[0]);
                newInterval[1] = max(newInterval[1], interval[1]);
                inserted = true;
            }
        }
        
        if (!inserted) {
            newIntervals.push_back(newInterval);
        }
        
        intervals = newIntervals;
    }
    
    vector<vector<int>> getIntervals() {
        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */