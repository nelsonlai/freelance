#include <vector>
#include <queue>

using namespace std;

class KthLargest {
private:
    int k;
    priority_queue<int, vector<int>, greater<int>> heap;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            heap.push(num);
        }
        while (heap.size() > k) {
            heap.pop();
        }
    }
    
    int add(int val) {
        heap.push(val);
        if (heap.size() > k) {
            heap.pop();
        }
        return heap.top();
    }
};
