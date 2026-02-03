#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size();
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        bool possible = false;
        for (int i = 1; i <= n / 2; i++) {
            if (total * i % n == 0) {
                possible = true;
                break;
            }
        }
        if (!possible) {
            return false;
        }
        
        vector<unordered_set<int>> sums(n / 2 + 1);
        sums[0].insert(0);
        
        for (int num : nums) {
            for (int i = sums.size() - 2; i >= 0; i--) {
                for (int s : sums[i]) {
                    sums[i + 1].insert(s + num);
                }
            }
        }
        
        for (int i = 1; i <= n / 2; i++) {
            if (total * i % n == 0) {
                int target = total * i / n;
                if (sums[i].find(target) != sums[i].end()) {
                    return true;
                }
            }
        }
        return false;
    }
};
