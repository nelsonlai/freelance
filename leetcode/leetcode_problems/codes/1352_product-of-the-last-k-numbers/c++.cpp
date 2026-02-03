/*
 * Problem: Product of the Last K Numbers
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Maintain prefix products, reset on 0, use division for last k
 * Time Complexity: O(1) for add, O(1) for getProduct
 * Space Complexity: O(n) for prefix products
 */

#include <vector>

using namespace std;

class ProductOfNumbers {
private:
    vector<int> prefix;

public:
    ProductOfNumbers() {
        prefix.push_back(1);
    }
    
    void add(int num) {
        if (num == 0) {
            prefix.clear();
            prefix.push_back(1);
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }
    
    int getProduct(int k) {
        if (k >= prefix.size()) {
            return 0;
        }
        return prefix.back() / prefix[prefix.size() - k - 1];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
