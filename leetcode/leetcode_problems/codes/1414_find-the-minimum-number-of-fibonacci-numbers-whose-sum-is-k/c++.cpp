/*
 * Problem: Find the Minimum Number of Fibonacci Numbers Whose Sum Is K
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: Generate Fibonacci numbers up to k, greedily subtract largest
 * Time Complexity: O(log k)
 * Space Complexity: O(log k) for Fibonacci list
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        vector<int> fib = {1, 1};
        
        while (fib.back() < k) {
            fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
        }
        
        int count = 0;
        int i = fib.size() - 1;
        while (k > 0) {
            if (fib[i] <= k) {
                k -= fib[i];
                count++;
            }
            i--;
        }
        
        return count;
    }
};