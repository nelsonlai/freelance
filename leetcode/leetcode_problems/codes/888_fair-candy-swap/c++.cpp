#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        int sumA = 0, sumB = 0;
        for (int size : aliceSizes) {
            sumA += size;
        }
        for (int size : bobSizes) {
            sumB += size;
        }
        
        int diff = (sumB - sumA) / 2;
        unordered_set<int> setB(bobSizes.begin(), bobSizes.end());
        
        for (int a : aliceSizes) {
            if (setB.find(a + diff) != setB.end()) {
                return {a, a + diff};
            }
        }
        
        return {};
    }
};
