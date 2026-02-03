"""
Problem: Encode and Decode TinyURL
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

import random
import string

class Codec:
    def __init__(self):
        self.url_map = {}
        self.base = "http://tinyurl.com/"
        self.chars = string.ascii_letters + string.digits

    def encode(self, longUrl: str) -> str:
        while True:
            short = ''.join(random.choice(self.chars) for _ in range(6))
            if short not in self.url_map:
                self.url_map[short] = longUrl
                return self.base + short

    def decode(self, shortUrl: str) -> str:
        short = shortUrl.replace(self.base, "")
        return self.url_map.get(short, "")