#include <vector>
#include <algorithm>

using namespace std;

class RangeModule {
private:
    vector<pair<int, int>> ranges;

public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        vector<pair<int, int>> newRanges;
        bool inserted = false;
        for (auto& range : ranges) {
            if (range.second < left) {
                newRanges.push_back(range);
            } else if (range.first > right) {
                if (!inserted) {
                    newRanges.push_back({left, right});
                    inserted = true;
                }
                newRanges.push_back(range);
            } else {
                left = min(left, range.first);
                right = max(right, range.second);
            }
        }
        if (!inserted) {
            newRanges.push_back({left, right});
        }
        ranges = newRanges;
    }
    
    bool queryRange(int left, int right) {
        for (auto& range : ranges) {
            if (range.first <= left && right <= range.second) {
                return true;
            }
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        vector<pair<int, int>> newRanges;
        for (auto& range : ranges) {
            if (range.second < left || range.first > right) {
                newRanges.push_back(range);
            } else {
                if (range.first < left) {
                    newRanges.push_back({range.first, left});
                }
                if (range.second > right) {
                    newRanges.push_back({right, range.second});
                }
            }
        }
        ranges = newRanges;
    }
};
