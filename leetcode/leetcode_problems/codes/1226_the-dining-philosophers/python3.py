"""
Problem: The Dining Philosophers
Difficulty: Medium
Tags: array

Approach: Use locks to prevent deadlock - acquire locks in order (lower index first)
Time Complexity: O(1) per operation
Space Complexity: O(1)
"""

import threading

class DiningPhilosophers:

    def __init__(self):
        self.locks = [threading.Lock() for _ in range(5)]

    # call the functions directly to execute, for example, eat()
    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:
        left = philosopher
        right = (philosopher + 1) % 5
        
        # Always acquire lower index first to prevent deadlock
        first, second = min(left, right), max(left, right)
        first_lock, second_lock = self.locks[first], self.locks[second]
        
        with first_lock:
            with second_lock:
                if first == left:
                    pickLeftFork()
                    pickRightFork()
                else:
                    pickRightFork()
                    pickLeftFork()
                
                eat()
                
                if first == left:
                    putRightFork()
                    putLeftFork()
                else:
                    putLeftFork()
                    putRightFork()