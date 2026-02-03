class Solution {
    fun strStr(haystack: String, needle: String): Int {
        if (needle.isEmpty()) {
            return 0
        }
        
        val n = haystack.length
        val m = needle.length
        
        for (i in 0..(n - m)) {
            if (haystack.substring(i, i + m) == needle) {
                return i
            }
        }
        
        return -1
    }
}