class Solution {
    fun longestPalindrome(s: String): String {
        if (s.isEmpty()) return ""
        
        var start = 0
        var maxLen = 1
        
        fun expandAroundCenter(left: Int, right: Int): Int {
            var left = left
            var right = right
            while (left >= 0 && right < s.length && s[left] == s[right]) {
                left--
                right++
            }
            return right - left - 1
        }
        
        for (i in s.indices) {
            val len1 = expandAroundCenter(i, i)
            val len2 = expandAroundCenter(i, i + 1)
            val len = maxOf(len1, len2)
            
            if (len > maxLen) {
                start = i - (len - 1) / 2
                maxLen = len
            }
        }
        
        return s.substring(start, start + maxLen)
    }
}