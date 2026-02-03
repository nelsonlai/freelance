#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++) {
            pos[row[i]] = i;
        }
        
        int swaps = 0;
        for (int i = 0; i < n; i += 2) {
            int partner = row[i] ^ 1;
            if (row[i + 1] != partner) {
                int j = pos[partner];
                swap(row[i + 1], row[j]);
                pos[row[i + 1]] = i + 1;
                pos[row[j]] = j;
                swaps++;
            }
        }
        
        return swaps;
    }
};
