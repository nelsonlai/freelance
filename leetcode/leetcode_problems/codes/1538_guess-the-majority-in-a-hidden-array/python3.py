"""
Problem: Guess the Majority in a Hidden Array
Difficulty: Medium
Tags: array, math

Approach: Use queries to determine values, count 0s and 1s, return index with minority or -1
Time Complexity: O(n) where n is array length
Space Complexity: O(1)
"""

# """
# This is the ArrayReader's API interface.
# You should not implement it, or speculate about its implementation
# """
#class ArrayReader(object):
#	 # Compares 4 different elements in the array
#	 # return 4 if the values of the 4 elements are the same (0 or 1).
#	 # return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
#	 # return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
#    def query(self, a: int, b: int, c: int, d: int) -> int:
#
#	 # Returns the length of the array
#    def length(self) -> int:
#

class Solution:
    def guessMajority(self, reader: 'ArrayReader') -> int:
        n = reader.length()
        # Assume arr[0] = 0, determine other values relative to it
        values = [0] * n
        count0 = 1
        count1 = 0
        
        # Determine arr[1], arr[2], arr[3] using queries
        q1 = reader.query(0, 1, 2, 3)
        if q1 == 4:
            values[1] = values[2] = values[3] = 0
            count0 += 3
        elif q1 == 0:
            # Two 0s and two 1s, need more queries
            q2 = reader.query(0, 1, 2, 4) if n > 4 else 0
            if q2 == 4:
                values[1] = values[2] = 0
                values[3] = 1
                count0 += 2
                count1 += 1
            elif q2 == 2:
                values[1] = values[2] = 0
                values[3] = 1
                count0 += 2
                count1 += 1
            else:
                # More complex case
                q3 = reader.query(0, 1, 3, 4) if n > 4 else 0
                if q3 == 4:
                    values[1] = values[3] = 0
                    values[2] = 1
                    count0 += 2
                    count1 += 1
                else:
                    values[1] = 0
                    values[2] = values[3] = 1
                    count0 += 1
                    count1 += 2
        else:  # q1 == 2
            # Three same, one different
            q2 = reader.query(0, 1, 2, 4) if n > 4 else 0
            if q2 == 4:
                values[1] = values[2] = 0
                values[3] = 1
                count0 += 2
                count1 += 1
            else:
                values[1] = 0
                values[2] = values[3] = 1
                count0 += 1
                count1 += 2
        
        # Determine remaining values
        for i in range(4, n):
            q = reader.query(0, 1, 2, i)
            if q == 4:
                values[i] = values[0]
                if values[i] == 0:
                    count0 += 1
                else:
                    count1 += 1
            elif q == 0:
                values[i] = 1 - values[0]
                if values[i] == 0:
                    count0 += 1
                else:
                    count1 += 1
            else:  # q == 2
                # Check with known values
                if values[1] == values[2]:
                    values[i] = 1 - values[1]
                else:
                    values[i] = values[1] if reader.query(0, 1, 3, i) == 4 else 1 - values[1]
                if values[i] == 0:
                    count0 += 1
                else:
                    count1 += 1
        
        if count0 == count1:
            return -1
        elif count0 < count1:
            for i in range(n):
                if values[i] == 0:
                    return i
        else:
            for i in range(n):
                if values[i] == 1:
                    return i
        return -1