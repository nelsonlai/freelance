#include <vector>
#include <algorithm>

using namespace std;

class MyCalendarTwo {
private:
    vector<pair<int, int>> events;
    vector<pair<int, int>> overlaps;

public:
    MyCalendarTwo() {
        
    }
    
    bool book(int startTime, int endTime) {
        for (auto& overlap : overlaps) {
            if (overlap.first < endTime && startTime < overlap.second) {
                return false;
            }
        }
        
        for (auto& event : events) {
            if (event.first < endTime && startTime < event.second) {
                overlaps.push_back({max(event.first, startTime), min(event.second, endTime)});
            }
        }
        
        events.push_back({startTime, endTime});
        return true;
    }
};
