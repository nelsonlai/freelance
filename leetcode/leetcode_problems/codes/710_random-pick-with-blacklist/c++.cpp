#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <random>

using namespace std;

class Solution {
private:
    int n;
    unordered_set<int> blacklist;
    vector<int> whitelist;
    int m;
    unordered_map<int, int> mapping;
    random_device rd;
    mt19937 gen;

public:
    Solution(int n, vector<int>& blacklist) : gen(rd()) {
        this->n = n;
        for (int num : blacklist) {
            this->blacklist.insert(num);
        }
        this->m = n - blacklist.size();
        
        if (blacklist.size() < n / 2) {
            for (int i = 0; i < n; i++) {
                if (this->blacklist.find(i) == this->blacklist.end()) {
                    this->whitelist.push_back(i);
                }
            }
        } else {
            int j = this->m;
            for (int num : blacklist) {
                if (num < this->m) {
                    while (this->blacklist.find(j) != this->blacklist.end()) {
                        j++;
                    }
                    this->mapping[num] = j;
                    j++;
                }
            }
        }
    }
    
    int pick() {
        if (blacklist.size() < n / 2) {
            uniform_int_distribution<> dis(0, whitelist.size() - 1);
            return whitelist[dis(gen)];
        } else {
            uniform_int_distribution<> dis(0, m - 1);
            int r = dis(gen);
            return mapping.find(r) != mapping.end() ? mapping[r] : r;
        }
    }
};
