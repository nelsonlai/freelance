'''
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

Example 1:
Input: n = 19, 62387879
Output: true
Explanation:
1^2 + 9^2 = 82 => 9^2 + 1^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
Return true because it ends in 1.

62387879 % 10 = 9
62387879 // 10 = 6238787
6238787 % 10 = 7
6238787 // 10 = 623878
623878 % 10 = 8
623878 // 10 = 62387
62387 % 10 = 7
62387 // 10 = 6238
6238 % 10 = 8
6238 // 10 = 623
623 % 10 = 3
623 // 10 = 62
62 % 10 = 2
62 // 10 = 6
6 % 10 = 6
6 // 10 = 0


Example 2:
Input: n = 2
Output: false
Explanation:
2^2 = 4
4^2 = 16
1^2 + 6^2 = 37
3^2 + 7^2 = 58
5^2 + 8^2 = 89
8^2 + 9^2 = 145
1^2 + 4^2 + 5^2 = 42
4^2 + 2^2 = 20
2^2 + 0^2 = 4
Return false because it loops endlessly in a cycle which does not include 1.
'''
from typing import Any


from ast import Set


def getNextNumber(number: int) -> int:
    nextNumber = 0
    while number > 0:
        nextNumber += (number % 10) ** 2
        number //= 10
    return nextNumber

def isHappyNumber(number: int) -> bool:
    seenNumbers = set[Any]() # to store the numbers we have seen
    while number != 1 and number not in seenNumbers:
        seenNumbers.add(number)
        number = getNextNumber(number)
    return number == 1

### Floyd's Cycle Detection Algorithm
def isHappyNumber(number: int) -> bool:
    slow = number
    fast = number
    while fast != 1 and fast != slow:
        slow = getNextNumber(slow)
        fast = getNextNumber(getNextNumber(fast))
    return fast == 1

