/*
 * Problem: Count Square Sum Triples
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Check all triplets (a, b, c) where a^2 + b^2 = c^2
 * Time Complexity: O(n^2) where n is limit
 * Space Complexity: O(1)
 */

#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
public:
    int countTriples(int n) {
        unordered_set<int> squares;
        for (int i = 1; i <= n; i++) {
            squares.insert(i * i);
        }
        
        int count = 0;
        for (int a = 1; a <= n; a++) {
            for (int b = a; b <= n; b++) {
                int cSquared = a * a + b * b;
                if (squares.find(cSquared) != squares.end()) {
                    int c = sqrt(cSquared);
                    if (c <= n) {
                        count += (a == b) ? 1 : 2;
                    }
                }
            }
        }
        
        return count;
    }
};