#include <set>
#include <map>
#include <vector>

using namespace std;

class ExamRoom {
private:
    int n;
    set<vector<int>> starts;
    map<int, vector<int>> startMap;
    map<int, vector<int>> endMap;
    
    int distance(int left, int right) {
        if (left == -1) return right;
        if (right == n) return n - 1 - left;
        return (right - left) / 2;
    }

public:
    ExamRoom(int n) {
        this->n = n;
        vector<int> interval = {-1, n};
        starts.insert(interval);
        startMap[-1] = interval;
        endMap[n] = interval;
    }
    
    int seat() {
        vector<int> interval = *starts.begin();
        starts.erase(starts.begin());
        int left = interval[0], right = interval[1];
        int seat;
        if (left == -1) {
            seat = 0;
        } else if (right == n) {
            seat = n - 1;
        } else {
            seat = (left + right) / 2;
        }
        
        vector<int> leftInterval = {left, seat};
        vector<int> rightInterval = {seat, right};
        starts.insert(leftInterval);
        starts.insert(rightInterval);
        startMap[left] = leftInterval;
        startMap[seat] = rightInterval;
        endMap[seat] = leftInterval;
        endMap[right] = rightInterval;
        
        return seat;
    }
    
    void leave(int p) {
        vector<int> leftInterval = endMap[p];
        vector<int> rightInterval = startMap[p];
        int left = leftInterval[0];
        int right = rightInterval[1];
        
        starts.erase(leftInterval);
        starts.erase(rightInterval);
        startMap.erase(left);
        startMap.erase(p);
        endMap.erase(p);
        endMap.erase(right);
        
        vector<int> newInterval = {left, right};
        starts.insert(newInterval);
        startMap[left] = newInterval;
        endMap[right] = newInterval;
    }
};
