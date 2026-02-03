# Chapter 2: Algorithm Analysis — Comprehensive Teaching Materials

**Source:** *Data Structures and Algorithm Analysis in C++*, 4th Edition, Mark Allen Weiss

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Mathematical Background](#2-mathematical-background)
3. [Model of Computation](#3-model-of-computation)
4. [What to Analyze](#4-what-to-analyze)
5. [Running-Time Calculations](#5-running-time-calculations)
6. [Maximum Subsequence Sum Problem](#6-maximum-subsequence-sum-problem)
7. [Logarithms in the Running Time](#7-logarithms-in-the-running-time)
8. [Limitations of Worst-Case Analysis](#8-limitations-of-worst-case-analysis)
9. [Summary and Key Takeaways](#9-summary-and-key-takeaways)

---

## 1. Introduction

An **algorithm** is a clearly specified set of simple instructions to be followed to solve a problem. Once an algorithm is correct, we must determine how much in the way of **resources** (time, space) it requires.

### Learning Objectives

- **Estimate** the time required for a program.
- **Reduce** running time from days or years to fractions of a second.
- Understand the **results of careless recursion** (e.g., naive Fibonacci).
- Implement **efficient algorithms** for exponentiation and GCD.

---

## 2. Mathematical Background

We need a formal framework to compare **growth rates** of functions (and thus of algorithms). We use asymptotic notation.

### 2.1 The Four Definitions

| Notation                  | Name      | Meaning (informal)                                   |
| ------------------------- | --------- | ---------------------------------------------------- |
| **T(N) = O(f(N))**  | Big-Oh    | T grows**at most as fast as** f (upper bound)  |
| **T(N) = Ω(g(N))** | Omega     | T grows**at least as fast as** g (lower bound) |
| **T(N) = Θ(h(N))** | Theta     | T grows**at the same rate as** h (tight bound) |
| **T(N) = o(p(N))**  | Little-oh | T grows **strictly slower than** p            |

### 2.2 Formal Definitions

- **Big-Oh:** T(N) = O(f(N)) if there exist positive constants **c** and **n₀** such that**T(N) ≤ c·f(N)** for all N ≥ n₀.
- **Omega:** T(N) = Ω(g(N)) if there exist positive constants c and n₀ such that**T(N) ≥ c·g(N)** for all N ≥ n₀.
- **Theta:** T(N) = Θ(h(N)) **if and only if** T(N) = O(h(N)) **and** T(N) = Ω(h(N)).
- **Little-oh:** T(N) = o(p(N)) if for **every** positive constant c there exists n₀ such that
  **T(N) < c·p(N)** for all N > n₀.
  Equivalently: T(N) = O(p(N)) but T(N) ≠ Θ(p(N)).

### 2.3 Intuition

- We compare **relative rates of growth**, not pointwise values.
- Example: 1000N vs N². For small N, 1000N is larger; for N > 1000, N² dominates. So **1000N = O(N²)** (we can take c = 1, n₀ = 1000).
- **Rule of thumb:** Drop constants and lower-order terms. 6N + 4 → O(N); 2N² + N → O(N²).

### 2.4 Important Rules

| Rule                           | Statement                                                                            |
| ------------------------------ | ------------------------------------------------------------------------------------ |
| **Rule 1 (Sums)**        | If T₁(N) = O(f(N)) and T₂(N) = O(g(N)), then T₁(N) + T₂(N) = O(max(f(N), g(N))). |
| **Rule 2 (Products)**    | T₁(N) · T₂(N) = O(f(N) · g(N)).                                                  |
| **Rule 3 (Polynomials)** | If T(N) is a polynomial of degree k, then T(N) = Θ(N^k).                            |
| **Rule 4 (Logarithms)**  | log^k N = O(N) for any constant k. Logarithms grow very slowly.                      |

### 2.5 Typical Growth Rates (Slow → Fast)

| Function | Name         |
| -------- | ------------ |
| c        | Constant     |
| log N    | Logarithmic  |
| log² N  | Log-squared  |
| N        | Linear       |
| N log N  | Linearithmic |
| N²      | Quadratic    |
| N³      | Cubic        |
| 2^N      | Exponential  |

### 2.6 Using Limits (L'Hôpital)

To compare f(N) and g(N), compute **lim_{N→∞} f(N)/g(N)**:

- Limit = 0 → f(N) = o(g(N))
- Limit = c ≠ 0 → f(N) = Θ(g(N))
- Limit = ∞ → g(N) = o(f(N))

### 2.7 Style Notes

- **Do not** write f(N) ≤ O(g(N)) (redundant) or f(N) ≥ O(g(N)) (meaningless).
- **Do not** put constants inside Big-Oh: write O(N²), not O(2N²).

---

## 3. Model of Computation

To analyze algorithms we assume a **simple computational model**:

- **Sequential** execution of instructions.
- **Simple operations** (addition, multiplication, comparison, assignment) each take **one time unit**.
- **Fixed-size integers** (e.g., 32-bit); no fancy operations (e.g., sorting) in one step.
- **Infinite memory** (we ignore paging/caching effects in the theory).

### Weaknesses of the Model

- In reality, not all operations take the same time (e.g., disk read vs add).
- Memory hierarchy and cache matter for large N.
- The model is still useful for **comparing algorithms** and **Big-Oh** analysis.

---

## 4. What to Analyze

The most important resource is usually **running time**. Factors:

- **Algorithm** and **input** (we control these).
- Compiler, machine (often ignored in theory).

### 4.1 Time Functions

- **T_avg(N):** average-case running time for input of size N.
- **T_worst(N):** worst-case running time.
- Clearly: T_avg(N) ≤ T_worst(N).

### 4.2 Why Worst-Case?

- Gives a **guarantee** for any input.
- Average-case is often **hard** to define and compute.
- Unless stated otherwise, **analyze worst-case**.

### 4.3 What We Analyze

We analyze **algorithms**, not particular programs. Implementation details (e.g., pass-by-reference vs copy) can affect constants but usually not the Big-Oh.

---

## 5. Running-Time Calculations

### 5.1 Strategy

1. **No fixed units:** throw away constants; answer in Big-Oh.
2. **Never underestimate:** Big-Oh is an upper bound; the program may be faster but not slower than the analysis.
3. **Inside out:** analyze innermost loops first, then nest.

### 5.2 General Rules for Code

| Rule                             | Description                                                   |
| -------------------------------- | ------------------------------------------------------------- |
| **For loop**               | Time = (time per iteration) × (number of iterations).        |
| **Nested loops**           | Time = product of sizes of all loops (for simple inner body). |
| **Consecutive statements** | Add times; the**maximum** dominates.                    |
| **If/else**                | Time = time(test) + max(time(S1), time(S2)).                  |

### 5.3 Simple Example: Sum of Cubes

```cpp
int sum(int n) {
    int partialSum = 0;           // O(1)
    for (int i = 1; i <= n; ++i)   // O(N) iterations
        partialSum += i * i * i;   // O(1) per iteration
    return partialSum;             // O(1)
}
```

Total: O(1) + O(N)·O(1) + O(1) = **O(N)**.

### 5.4 Recursion: When Is It Easy?

- If recursion is just a “thin” loop (e.g., factorial: one call per step), then **T(N) = O(N)**.
- If recursion splits into **multiple** subproblems (e.g., fib(n-1) and fib(n-2)), we get a **recurrence** and must solve it (or recognize a pattern).

### 5.5 Naive Fibonacci: A Warning

- T(N) = T(N−1) + T(N−2) + O(1) ⇒ T(N) ≥ fib(N) ≈ φ^N (exponential).
- **Cause:** redundant work; same subproblems solved many times.
- **Fix:** memoization or iterative (dynamic programming) → O(N) time, O(1) space.

---

## 6. Maximum Subsequence Sum Problem

**Problem:** Given (possibly negative) integers A₁, A₂, …, A_N, find the maximum value of
**∑_{k=i}^{j} A_k** (over all i ≤ j). If all are negative, the answer is 0.

**Example:** For −2, 11, −4, 13, −5, −2, the answer is 20 (elements 11, −4, 13).

### 6.1 Algorithm 1 — Exhaustive (Cubic)

- Three nested loops: for each i, for each j ≥ i, for each k from i to j, sum and compare.
- **Time:** O(N³). **Space:** O(1).

### 6.2 Algorithm 2 — Improved (Quadratic)

- For each starting index i, extend j and maintain running sum; no inner loop over k.
- Uses: ∑_{k=i}^{j} A_k = A_j + ∑_{k=i}^{j−1} A_k.
- **Time:** O(N²). **Space:** O(1).

### 6.3 Algorithm 3 — Divide and Conquer (Linearithmic)

- **Divide:** split array at center.
- **Conquer:** recursively solve left half and right half.
- **Combine:** find max sum that **crosses** the middle (max suffix of left + max prefix of right); return max(leftMax, rightMax, crossMax).
- Recurrence: T(N) = 2T(N/2) + O(N) ⇒ **T(N) = O(N log N)**.

### 6.4 Algorithm 4 — Linear (Kadane-style)

- Single pass: for each j, maintain “best sum ending at j” and reset to 0 if it becomes negative.
- **Observation:** if a[i..j] has negative sum, we can skip starting at any index in [i, j]; advance start to j+1.
- **Time:** O(N). **Space:** O(1). **Online:** can process stream; constant space.

### 6.5 Comparison (Weiss, Fig. 2.2)

| N      | Alg 1 (O(N³)) | Alg 2 (O(N²)) | Alg 3 (O(N log N)) | Alg 4 (O(N)) |
| ------ | -------------- | -------------- | ------------------ | ------------ |
| 100    | ~0.0002 s      | ~0.000006 s    | ~0.000005 s        | ~0.000002 s  |
| 10,000 | ~87 s          | ~0.03 s        | ~0.0006 s          | ~0.0002 s    |

For large N, only linear and linearithmic are practical.

---

## 7. Logarithms in the Running Time

### 7.1 When Do We See O(log N)?

- **Divide-and-conquer** that cuts problem size by a **constant factor** (e.g., half) per step: typically O(log N) steps.
- If we only **reduce by a constant amount** (e.g., N → N−1) per step, we get O(N).

### 7.2 Binary Search

- **Input:** Sorted array A, value X.
- **Process:** Compare X with middle; if equal, return; if smaller, search left half; if larger, search right half.
- Each step halves the range ⇒ at most **⌈log₂ N⌉ + O(1)** comparisons ⇒ **O(log N)**.
- **Assumption:** Input is already in memory (reading N elements would be Ω(N)).

### 7.3 Euclid’s Algorithm (GCD)

- **gcd(M, N)** with M ≥ N: replace (M, N) by (N, M mod N) until N = 0; answer is M.
- **Theorem:** After two iterations, remainder is at most half of its previous value ⇒ **O(log N)** iterations (with N = max(M, N)).
- **Note:** Average-case analysis is much deeper; worst-case still O(log N).

### 7.4 Efficient Exponentation (X^N)

- **Naive:** N−1 multiplications ⇒ O(N).
- **Recursive:** X^N = (X^{N/2})² if N even; X^N = (X^{(N−1)/2})² · X if N odd ⇒ at most **2 log N** multiplications ⇒ **O(log N)**.
- **Pitfall:** Using two recursive calls (e.g., pow(x, N/2) * pow(x, N/2)) makes it O(N) again.

---

## 8. Limitations of Worst-Case Analysis

- Worst-case can be **pessimistic**: some algorithms perform much better on average.
- **Average-case** is often very hard (or unsolved); worst-case is a **safe guarantee**.
- For many algorithms, worst-case is **achievable** by some bad input but rare in practice.
- **Lower-bound analysis** (e.g., comparison-based sorting ≥ Ω(N log N)) applies to *all* algorithms in a class and is typically harder than analyzing one algorithm.

---

## 9. Summary and Key Takeaways

1. **Big-Oh** gives an upper bound; **Omega** lower; **Theta** tight; **little-oh** strictly smaller.
2. **Drop constants and lower-order terms** when giving Big-Oh.
3. **Model:** one time unit per simple operation; sequential; infinite memory.
4. **Analyze worst-case** unless stated otherwise; analyze **algorithms**, not just one program.
5. **Rules:** loops multiply; consecutive blocks add (max dominates); recursion → recurrence.
6. **Maximum subsequence sum:** four algorithms from O(N³) to O(N); linear algorithm is online and O(1) space.
7. **O(log N)** appears when we **halve** (or cut by a factor) the problem size each step (binary search, GCD, exponentiation).
8. **Naive recursion** (e.g., fib) can be exponential; iterative or memoized version is polynomial.

---

## C++ Code Examples Reference

The following C++ files accompany this chapter (all heavily commented):

| File                            | Content                                                 | Complexity                       |
| ------------------------------- | ------------------------------------------------------- | -------------------------------- |
| `ch2_sum_of_cubes.cpp`        | Sum ∑i³; simple loop; closed-form formula             | O(N) and O(1)                    |
| `ch2_loop_rules.cpp`          | Nested loops, consecutive statements (Rules 1–3)       | O(N), O(N²)                     |
| `ch2_max_subsequence_sum.cpp` | All four max subsequence sum algorithms                 | O(N³), O(N²), O(N log N), O(N) |
| `ch2_binary_search.cpp`       | Binary search in sorted array (iterative and recursive) | O(log N)                         |
| `ch2_gcd_exponentiation.cpp`  | Euclid’s GCD and efficient pow(X, N)                   | O(log N)                         |
| `ch2_fibonacci_analysis.cpp`  | Naive recursive vs iterative Fibonacci                  | O(φ^N) vs O(N)                  |

**Compile (example):**

```bash
g++ -std=c++11 -o ch2_sum_of_cubes ch2_sum_of_cubes.cpp
g++ -std=c++11 -o ch2_max_subsequence_sum ch2_max_subsequence_sum.cpp
# ... similarly for other files
```

Run each program to reinforce the relationship between code structure and asymptotic running time.
