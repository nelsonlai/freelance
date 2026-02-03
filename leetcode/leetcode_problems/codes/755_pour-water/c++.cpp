#include <vector>

using namespace std;

class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        for (int v = 0; v < volume; v++) {
            int pos = k;
            
            // Try to move left
            while (pos > 0 && heights[pos] >= heights[pos - 1]) {
                pos--;
            }
            
            // Try to move right if can't move left
            if (pos == k) {
                while (pos < heights.size() - 1 && heights[pos] >= heights[pos + 1]) {
                    pos++;
                }
                while (pos > k && heights[pos] == heights[pos - 1]) {
                    pos--;
                }
            }
            
            heights[pos]++;
        }
        
        return heights;
    }
};
