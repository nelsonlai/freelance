#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        unordered_map<int, int> count;
        for (int card : deck) {
            count[card]++;
        }
        
        int gcd = 0;
        for (auto& pair : count) {
            gcd = getGcd(gcd, pair.second);
        }
        
        return gcd >= 2;
    }
    
private:
    int getGcd(int a, int b) {
        return b == 0 ? a : getGcd(b, a % b);
    }
};
