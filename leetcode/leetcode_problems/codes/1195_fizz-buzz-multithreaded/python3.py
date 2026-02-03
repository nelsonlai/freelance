"""
Problem: Fizz Buzz Multithreaded
Difficulty: Medium
Tags: general

Approach: Use threading locks and condition variables to coordinate threads
Time Complexity: O(n) where n is the number
Space Complexity: O(1)
"""

import threading

class FizzBuzz:
    def __init__(self, n: int):
        self.n = n
        self.current = 1
        self.lock = threading.Lock()
        self.condition = threading.Condition(self.lock)

    # printFizz() outputs "fizz"
    def fizz(self, printFizz: 'Callable[[], None]') -> None:
        while True:
            with self.condition:
                while self.current <= self.n and (self.current % 3 != 0 or self.current % 5 == 0):
                    self.condition.wait()
                if self.current > self.n:
                    return
                printFizz()
                self.current += 1
                self.condition.notify_all()

    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz: 'Callable[[], None]') -> None:
        while True:
            with self.condition:
                while self.current <= self.n and (self.current % 5 != 0 or self.current % 3 == 0):
                    self.condition.wait()
                if self.current > self.n:
                    return
                printBuzz()
                self.current += 1
                self.condition.notify_all()

    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz: 'Callable[[], None]') -> None:
        while True:
            with self.condition:
                while self.current <= self.n and (self.current % 3 != 0 or self.current % 5 != 0):
                    self.condition.wait()
                if self.current > self.n:
                    return
                printFizzBuzz()
                self.current += 1
                self.condition.notify_all()

    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber: 'Callable[[int], None]') -> None:
        while True:
            with self.condition:
                while self.current <= self.n and (self.current % 3 == 0 or self.current % 5 == 0):
                    self.condition.wait()
                if self.current > self.n:
                    return
                printNumber(self.current)
                self.current += 1
                self.condition.notify_all()