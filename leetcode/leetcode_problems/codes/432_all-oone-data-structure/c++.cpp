/*
 * Problem: All O`one Data Structure
 * Difficulty: Hard
 * Tags: string, hash, linked_list
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class AllOne {
private:
    unordered_map<string, int> count;
    int minCount;
    int maxCount;

public:
    AllOne() {
        minCount = INT_MAX;
        maxCount = 0;
    }
    
    void inc(string key) {
        count[key]++;
        int cnt = count[key];
        maxCount = max(maxCount, cnt);
        if (cnt == 1) {
            minCount = min(minCount, 1);
        } else {
            if (minCount == cnt - 1) {
                minCount = INT_MAX;
                for (auto& entry : count) {
                    if (entry.second > 0) {
                        minCount = min(minCount, entry.second);
                    }
                }
            }
        }
    }
    
    void dec(string key) {
        if (count.find(key) != count.end()) {
            count[key]--;
            if (count[key] == 0) {
                count.erase(key);
                if (count.empty()) {
                    minCount = INT_MAX;
                    maxCount = 0;
                } else {
                    minCount = INT_MAX;
                    maxCount = 0;
                    for (auto& entry : count) {
                        minCount = min(minCount, entry.second);
                        maxCount = max(maxCount, entry.second);
                    }
                }
            } else {
                minCount = INT_MAX;
                for (auto& entry : count) {
                    minCount = min(minCount, entry.second);
                }
                if (maxCount == count[key] + 1) {
                    maxCount = 0;
                    for (auto& entry : count) {
                        maxCount = max(maxCount, entry.second);
                    }
                }
            }
        }
    }
    
    string getMaxKey() {
        if (count.empty()) {
            return "";
        }
        for (auto& entry : count) {
            if (entry.second == maxCount) {
                return entry.first;
            }
        }
        return "";
    }
    
    string getMinKey() {
        if (count.empty()) {
            return "";
        }
        for (auto& entry : count) {
            if (entry.second == minCount) {
                return entry.first;
            }
        }
        return "";
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */