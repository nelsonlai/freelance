"""
Problem: Design Movie Rental System
Difficulty: Hard
Tags: array, hash, sort, search, queue, heap

Approach: Use heaps to track available and rented movies
Time Complexity: O(log n) for search, rent, drop; O(k log n) for report
Space Complexity: O(n)
"""

import heapq
from collections import defaultdict

class MovieRentingSystem:

    def __init__(self, n: int, entries: List[List[int]]):
        self.available = defaultdict(list)  # movie -> [(price, shop)]
        self.rented = []  # [(price, shop, movie)]
        self.shop_movie = {}  # (shop, movie) -> price
        self.rented_set = set()  # (shop, movie)
        
        for shop, movie, price in entries:
            heapq.heappush(self.available[movie], (price, shop))
            self.shop_movie[(shop, movie)] = price

    def search(self, movie: int) -> List[int]:
        result = []
        temp = []
        
        while len(result) < 5 and self.available[movie]:
            price, shop = heapq.heappop(self.available[movie])
            if (shop, movie) not in self.rented_set:
                result.append(shop)
            temp.append((price, shop))
        
        for item in temp:
            heapq.heappush(self.available[movie], item)
        
        return result

    def rent(self, shop: int, movie: int) -> None:
        price = self.shop_movie[(shop, movie)]
        self.rented_set.add((shop, movie))
        heapq.heappush(self.rented, (price, shop, movie))

    def drop(self, shop: int, movie: int) -> None:
        self.rented_set.remove((shop, movie))

    def report(self) -> List[List[int]]:
        result = []
        temp = []
        
        while len(result) < 5 and self.rented:
            price, shop, movie = heapq.heappop(self.rented)
            if (shop, movie) in self.rented_set:
                result.append([shop, movie])
            temp.append((price, shop, movie))
        
        for item in temp:
            heapq.heappush(self.rented, item)
        
        return result