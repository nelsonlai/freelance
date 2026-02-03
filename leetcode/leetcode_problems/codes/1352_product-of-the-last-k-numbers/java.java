/**
 * Problem: Product of the Last K Numbers
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Maintain prefix products, reset on 0, use division for last k
 * Time Complexity: O(1) for add, O(1) for getProduct
 * Space Complexity: O(n) for prefix products
 */

import java.util.*;

class ProductOfNumbers {
    private List<Integer> prefix;

    public ProductOfNumbers() {
        prefix = new ArrayList<>();
        prefix.add(1);
    }
    
    public void add(int num) {
        if (num == 0) {
            prefix = new ArrayList<>();
            prefix.add(1);
        } else {
            prefix.add(prefix.get(prefix.size() - 1) * num);
        }
    }
    
    public int getProduct(int k) {
        if (k >= prefix.size()) {
            return 0;
        }
        return prefix.get(prefix.size() - 1) / prefix.get(prefix.size() - k - 1);
    }
}

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers obj = new ProductOfNumbers();
 * obj.add(num);
 * int param_2 = obj.getProduct(k);
 */
