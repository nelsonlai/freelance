/*
 * Problem: Two Sum III - Data structure design
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>

using namespace std;

class TwoSum {
private:
    unordered_map<int, int> numbers;

public:
    TwoSum() {
        
    }
    
    void add(int number) {
        numbers[number]++;
    }
    
    bool find(int value) {
        for (auto& p : numbers) {
            int num = p.first;
            int complement = value - num;
            if (numbers.find(complement) != numbers.end()) {
                if (complement != num || numbers[complement] > 1) {
                    return true;
                }
            }
        }
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */