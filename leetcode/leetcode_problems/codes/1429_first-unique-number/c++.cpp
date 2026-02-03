/*
 * Problem: First Unique Number
 * Difficulty: Medium
 * Tags: array, hash, queue
 * 
 * Approach: Use map to track counts, list to maintain order of unique numbers
 * Time Complexity: O(1) for showFirstUnique, O(1) for add
 * Space Complexity: O(n) for counts and list
 */

#include <unordered_map>
#include <list>

using namespace std;

class FirstUnique {
private:
    unordered_map<int, int> count;
    list<int> unique;

public:
    FirstUnique(vector<int>& nums) {
        for (int num : nums) {
            add(num);
        }
    }
    
    int showFirstUnique() {
        if (!unique.empty()) {
            return unique.front();
        }
        return -1;
    }
    
    void add(int value) {
        if (count.find(value) == count.end()) {
            count[value] = 1;
            unique.push_back(value);
        } else {
            count[value]++;
            auto it = find(unique.begin(), unique.end(), value);
            if (it != unique.end()) {
                unique.erase(it);
            }
        }
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */