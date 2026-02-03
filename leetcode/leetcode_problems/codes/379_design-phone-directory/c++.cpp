/*
 * Problem: Design Phone Directory
 * Difficulty: Medium
 * Tags: array, hash, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_set>

using namespace std;

class PhoneDirectory {
private:
    unordered_set<int> available;
    unordered_set<int> used;

public:
    PhoneDirectory(int maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.insert(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        int number = *available.begin();
        available.erase(number);
        used.insert(number);
        return number;
    }
    
    bool check(int number) {
        return available.find(number) != available.end();
    }
    
    void release(int number) {
        if (used.find(number) != used.end()) {
            used.erase(number);
            available.insert(number);
        }
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */