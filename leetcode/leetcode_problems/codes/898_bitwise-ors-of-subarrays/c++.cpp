#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> result;
        unordered_set<int> cur;
        cur.insert(0);
        
        for (int x : arr) {
            unordered_set<int> next;
            for (int y : cur) {
                next.insert(x | y);
            }
            next.insert(x);
            cur = next;
            result.insert(cur.begin(), cur.end());
        }
        
        return result.size();
    }
};
