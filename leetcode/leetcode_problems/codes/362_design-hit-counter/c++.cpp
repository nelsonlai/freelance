/*
 * Problem: Design Hit Counter
 * Difficulty: Medium
 * Tags: array, search, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <queue>

using namespace std;

class HitCounter {
private:
    queue<int> hits;

public:
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        hits.push(timestamp);
    }
    
    int getHits(int timestamp) {
        while (!hits.empty() && hits.front() <= timestamp - 300) {
            hits.pop();
        }
        return hits.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */