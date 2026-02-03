/*
 * Problem: Insert Delete GetRandom O(1) - Duplicates allowed
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

using namespace std;

class RandomizedCollection {
private:
    vector<int> nums;
    unordered_map<int, unordered_set<int>> valToIndices;

public:
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        valToIndices[val].insert(nums.size());
        nums.push_back(val);
        return valToIndices[val].size() == 1;
    }
    
    bool remove(int val) {
        if (valToIndices.find(val) == valToIndices.end() || valToIndices[val].empty()) {
            return false;
        }
        
        int idx = *valToIndices[val].begin();
        valToIndices[val].erase(idx);
        int lastVal = nums.back();
        
        nums[idx] = lastVal;
        valToIndices[lastVal].insert(idx);
        valToIndices[lastVal].erase(nums.size() - 1);
        
        nums.pop_back();
        return true;
    }
    
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */