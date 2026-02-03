"""
Problem: Print in Order
Difficulty: Easy
Tags: general

Approach: Use threading locks to ensure execution order
Time Complexity: O(1) per method call
Space Complexity: O(1)
"""

import threading

class Foo:
    def __init__(self):
        self.lock1 = threading.Lock()
        self.lock2 = threading.Lock()
        self.lock1.acquire()
        self.lock2.acquire()

    def first(self, printFirst: 'Callable[[], None]') -> None:
        printFirst()
        self.lock1.release()

    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.lock1.acquire()
        printSecond()
        self.lock2.release()

    def third(self, printThird: 'Callable[[], None]') -> None:
        self.lock2.acquire()
        printThird()