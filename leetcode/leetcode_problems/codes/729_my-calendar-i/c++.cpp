#include <vector>

using namespace std;

class MyCalendar {
private:
    vector<pair<int, int>> events;

public:
    MyCalendar() {
        
    }
    
    bool book(int startTime, int endTime) {
        for (auto& event : events) {
            if (event.first < endTime && startTime < event.second) {
                return false;
            }
        }
        events.push_back({startTime, endTime});
        return true;
    }
};
