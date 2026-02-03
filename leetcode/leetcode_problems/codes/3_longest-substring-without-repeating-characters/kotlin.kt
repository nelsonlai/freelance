class Solution {
    fun lengthOfLongestSubstring(s: String): Int {
        val charIndex = mutableMapOf<Char, Int>()
        var left = 0
        var maxLen = 0
        
        for (right in s.indices) {
            val c = s[right]
            if (charIndex.containsKey(c) && charIndex[c]!! >= left) {
                left = charIndex[c]!! + 1
            }
            charIndex[c] = right
            maxLen = maxOf(maxLen, right - left + 1)
        }
        
        return maxLen
    }
}