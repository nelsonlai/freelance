"""
Problem: Design Authentication Manager
Difficulty: Medium
Tags: string, hash, design

Approach: Use dictionary to store token expiration times
Time Complexity: O(1) for generate/renew, O(n) for countUnexpiredTokens
Space Complexity: O(n)
"""

class AuthenticationManager:

    def __init__(self, timeToLive: int):
        self.timeToLive = timeToLive
        self.tokens = {}

    def generate(self, tokenId: str, currentTime: int) -> None:
        self.tokens[tokenId] = currentTime + self.timeToLive

    def renew(self, tokenId: str, currentTime: int) -> None:
        if tokenId in self.tokens and self.tokens[tokenId] > currentTime:
            self.tokens[tokenId] = currentTime + self.timeToLive

    def countUnexpiredTokens(self, currentTime: int) -> int:
        return sum(1 for exp_time in self.tokens.values() if exp_time > currentTime)