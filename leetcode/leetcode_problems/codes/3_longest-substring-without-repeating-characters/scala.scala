import scala.collection.mutable

object Solution {
    def lengthOfLongestSubstring(s: String): Int = {
        val charIndex = mutable.Map[Char, Int]()
        var left = 0
        var maxLen = 0
        
        for (right <- s.indices) {
            val c = s(right)
            if (charIndex.contains(c) && charIndex(c) >= left) {
                left = charIndex(c) + 1
            }
            charIndex(c) = right
            maxLen = math.max(maxLen, right - left + 1)
        }
        
        maxLen
    }
}