/*
 * Problem: Insert Delete GetRandom O(1)
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> valToIdx;

public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if (valToIdx.find(val) != valToIdx.end()) {
            return false;
        }
        valToIdx[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (valToIdx.find(val) == valToIdx.end()) {
            return false;
        }
        
        int idx = valToIdx[val];
        int lastVal = nums.back();
        nums[idx] = lastVal;
        valToIdx[lastVal] = idx;
        
        nums.pop_back();
        valToIdx.erase(val);
        return true;
    }
    
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */