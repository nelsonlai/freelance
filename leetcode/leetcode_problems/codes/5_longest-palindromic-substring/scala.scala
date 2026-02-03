object Solution {
    def longestPalindrome(s: String): String = {
        if (s.isEmpty) return ""
        
        var start = 0
        var maxLen = 1
        
        def expandAroundCenter(left: Int, right: Int): Int = {
            var left = left
            var right = right
            while (left >= 0 && right < s.length && s(left) == s(right)) {
                left -= 1
                right += 1
            }
            right - left - 1
        }
        
        for (i <- s.indices) {
            val len1 = expandAroundCenter(i, i)
            val len2 = expandAroundCenter(i, i + 1)
            val len = math.max(len1, len2)
            
            if (len > maxLen) {
                start = i - (len - 1) / 2
                maxLen = len
            }
        }
        
        s.substring(start, start + maxLen)
    }
}