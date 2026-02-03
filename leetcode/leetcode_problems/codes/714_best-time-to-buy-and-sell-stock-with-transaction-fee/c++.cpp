#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int hold = -prices[0];
        int sold = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            hold = max(hold, sold - prices[i]);
            sold = max(sold, hold + prices[i] - fee);
        }
        
        return sold;
    }
};
