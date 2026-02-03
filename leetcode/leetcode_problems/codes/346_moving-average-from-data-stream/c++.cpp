/*
 * Problem: Moving Average from Data Stream
 * Difficulty: Easy
 * Tags: array, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <queue>

using namespace std;

class MovingAverage {
private:
    int size;
    queue<int> q;
    double sum;

public:
    MovingAverage(int size) {
        this->size = size;
        this->sum = 0;
    }
    
    double next(int val) {
        q.push(val);
        sum += val;
        if (q.size() > size) {
            sum -= q.front();
            q.pop();
        }
        return sum / q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */