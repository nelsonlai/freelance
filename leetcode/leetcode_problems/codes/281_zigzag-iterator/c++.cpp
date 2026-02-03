/*
 * Problem: Zigzag Iterator
 * Difficulty: Medium
 * Tags: array, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>

using namespace std;

class ZigzagIterator {
private:
    queue<pair<int, vector<int>*>> q;

public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) {
            q.push({0, &v1});
        }
        if (!v2.empty()) {
            q.push({0, &v2});
        }
    }

    int next() {
        auto [index, vec] = q.front();
        q.pop();
        int val = (*vec)[index];
        index++;
        if (index < vec->size()) {
            q.push({index, vec});
        }
        return val;
    }

    bool hasNext() {
        return !q.empty();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */