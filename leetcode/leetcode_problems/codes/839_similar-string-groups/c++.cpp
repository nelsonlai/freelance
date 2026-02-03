#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    vector<int> parent;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void union_set(int x, int y) {
        parent[find(x)] = find(y);
    }
    
    bool similar(string& a, string& b) {
        int diff = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) {
                diff++;
            }
        }
        return diff == 0 || diff == 2;
    }

public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (similar(strs[i], strs[j])) {
                    union_set(i, j);
                }
            }
        }
        
        unordered_set<int> groups;
        for (int i = 0; i < n; i++) {
            groups.insert(find(i));
        }
        return groups.size();
    }
};
