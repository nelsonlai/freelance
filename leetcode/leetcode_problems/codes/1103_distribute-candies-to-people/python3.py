"""
Problem: Distribute Candies to People
Difficulty: Easy
Tags: array, math

Approach: Simulate distribution round by round
Time Complexity: O(sqrt(candies))
Space Complexity: O(num_people)
"""

class Solution:
    def distributeCandies(self, candies: int, num_people: int) -> List[int]:
        result = [0] * num_people
        round_num = 0
        
        while candies > 0:
            for i in range(num_people):
                give = round_num * num_people + i + 1
                if candies >= give:
                    result[i] += give
                    candies -= give
                else:
                    result[i] += candies
                    candies = 0
                    break
            round_num += 1
        
        return result