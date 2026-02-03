#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool canFinish(vector<int>& piles, int h, int speed) {
        int time = 0;
        for (int pile : piles) {
            time += (pile + speed - 1) / speed;
        }
        return time <= h;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (canFinish(piles, h, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
