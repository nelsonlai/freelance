/*
 * Problem: Prime Arrangements
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Count primes using Sieve of Eratosthenes, calculate factorial of prime and non-prime counts
 * Time Complexity: O(n log log n) for sieve + O(n) for factorial
 * Space Complexity: O(n) for sieve array
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numPrimeArrangements(int n) {
        const int MOD = 1e9 + 7;
        int primeCount = countPrimes(n);
        int nonPrimeCount = n - primeCount;
        return (factorialMod(primeCount, MOD) * factorialMod(nonPrimeCount, MOD)) % MOD;
    }
    
private:
    int countPrimes(int n) {
        if (n < 2) {
            return 0;
        }
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;
        
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        return count(isPrime.begin(), isPrime.end(), true);
    }
    
    long long factorialMod(int k, int MOD) {
        long long result = 1;
        for (int i = 2; i <= k; i++) {
            result = (result * i) % MOD;
        }
        return result;
    }
};