/*
 * Problem: Map Sum Pairs
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class MapSum {
private:
    unordered_map<string, int> map;
    unordered_map<string, int> prefixMap;

public:
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        int delta = val - map[key];
        map[key] = val;
        
        for (int i = 1; i <= key.length(); i++) {
            string prefix = key.substr(0, i);
            prefixMap[prefix] += delta;
        }
    }
    
    int sum(string prefix) {
        return prefixMap[prefix];
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */