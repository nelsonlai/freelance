/*
 * Problem: Number of Recent Calls
 * Difficulty: Easy
 * Tags: queue
 * 
 * Approach: Use deque to maintain calls within [t-3000, t] range
 * Time Complexity: O(1) amortized per ping
 * Space Complexity: O(n) for storing calls
 */

#include <queue>

using namespace std;

class RecentCounter {
private:
    queue<int> q;

public:
    RecentCounter() {
        
    }
    
    int ping(int t) {
        q.push(t);
        while (q.front() < t - 3000) {
            q.pop();
        }
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */