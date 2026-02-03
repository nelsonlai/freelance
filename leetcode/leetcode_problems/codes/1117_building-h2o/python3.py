"""
Problem: Building H2O
Difficulty: Medium
Tags: general

Approach: Use threading locks and condition variables to ensure 2H + 1O pattern
Time Complexity: O(1) per method call
Space Complexity: O(1)
"""

import threading

class H2O:
    def __init__(self):
        self.lock = threading.Lock()
        self.h_count = 0
        self.o_count = 0
        self.h_condition = threading.Condition(self.lock)
        self.o_condition = threading.Condition(self.lock)

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        with self.lock:
            while self.h_count >= 2:
                self.h_condition.wait()
            self.h_count += 1
            if self.h_count == 2 and self.o_count == 1:
                releaseHydrogen()
                self.h_count = 0
                self.o_count = 0
                self.h_condition.notify_all()
                self.o_condition.notify_all()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        with self.lock:
            while self.o_count >= 1:
                self.o_condition.wait()
            self.o_count += 1
            if self.h_count == 2 and self.o_count == 1:
                releaseOxygen()
                self.h_count = 0
                self.o_count = 0
                self.h_condition.notify_all()
                self.o_condition.notify_all()