"""
Problem: LFU Cache
Difficulty: Hard
Tags: hash, linked_list

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

from collections import defaultdict, OrderedDict

class LFUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.min_freq = 0
        self.key_to_freq = {}
        self.freq_to_keys = defaultdict(OrderedDict)

    def get(self, key: int) -> int:
        if key not in self.key_to_freq:
            return -1
        
        freq = self.key_to_freq[key]
        value = self.freq_to_keys[freq][key]
        
        del self.freq_to_keys[freq][key]
        if not self.freq_to_keys[freq] and freq == self.min_freq:
            self.min_freq += 1
        
        self.key_to_freq[key] = freq + 1
        self.freq_to_keys[freq + 1][key] = value
        self.freq_to_keys[freq + 1].move_to_end(key)
        
        return value

    def put(self, key: int, value: int) -> None:
        if self.capacity == 0:
            return
        
        if key in self.key_to_freq:
            self.get(key)
            self.freq_to_keys[self.key_to_freq[key]][key] = value
            return
        
        if len(self.key_to_freq) >= self.capacity:
            lfu_key, _ = self.freq_to_keys[self.min_freq].popitem(last=False)
            del self.key_to_freq[lfu_key]
        
        self.key_to_freq[key] = 1
        self.freq_to_keys[1][key] = value
        self.freq_to_keys[1].move_to_end(key)
        self.min_freq = 1