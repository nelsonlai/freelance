/**
 * Problem: Prime Arrangements
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Count primes using Sieve of Eratosthenes, calculate factorial of prime and non-prime counts
 * Time Complexity: O(n log log n) for sieve + O(n) for factorial
 * Space Complexity: O(n) for sieve array
 */
import java.util.Arrays;

class Solution {
    private static final int MOD = 1_000_000_007;
    
    public int numPrimeArrangements(int n) {
        int primeCount = countPrimes(n);
        int nonPrimeCount = n - primeCount;
        return (int) ((factorialMod(primeCount) * factorialMod(nonPrimeCount)) % MOD);
    }
    
    private int countPrimes(int n) {
        if (n < 2) {
            return 0;
        }
        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        int count = 0;
        for (boolean prime : isPrime) {
            if (prime) {
                count++;
            }
        }
        return count;
    }
    
    private long factorialMod(int k) {
        long result = 1;
        for (int i = 2; i <= k; i++) {
            result = (result * i) % MOD;
        }
        return result;
    }
}