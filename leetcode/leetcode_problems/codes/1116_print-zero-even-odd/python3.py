"""
Problem: Print Zero Even Odd
Difficulty: Medium
Tags: general

Approach: Use threading locks to coordinate zero, even, and odd threads
Time Complexity: O(n) where n is the number
Space Complexity: O(1)
"""

import threading

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.zero_lock = threading.Lock()
        self.even_lock = threading.Lock()
        self.odd_lock = threading.Lock()
        self.even_lock.acquire()
        self.odd_lock.acquire()
        self.current = 1
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(self.n):
            self.zero_lock.acquire()
            printNumber(0)
            if self.current % 2 == 1:
                self.odd_lock.release()
            else:
                self.even_lock.release()

    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n + 1, 2):
            self.even_lock.acquire()
            printNumber(i)
            self.current += 1
            if self.current <= self.n:
                self.zero_lock.release()

    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            self.odd_lock.acquire()
            printNumber(i)
            self.current += 1
            if self.current <= self.n:
                self.zero_lock.release()