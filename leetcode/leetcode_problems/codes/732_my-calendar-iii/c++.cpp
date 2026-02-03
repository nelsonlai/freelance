#include <map>

using namespace std;

class MyCalendarThree {
private:
    map<int, int> delta;

public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        delta[startTime]++;
        delta[endTime]--;
        
        int active = 0;
        int maxActive = 0;
        for (auto& entry : delta) {
            active += entry.second;
            maxActive = max(maxActive, active);
        }
        
        return maxActive;
    }
};
