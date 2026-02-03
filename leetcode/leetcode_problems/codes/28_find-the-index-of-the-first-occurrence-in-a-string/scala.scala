object Solution {
    def strStr(haystack: String, needle: String): Int = {
        if (needle.isEmpty) {
            return 0
        }
        
        val n = haystack.length
        val m = needle.length
        
        for (i <- 0 to (n - m)) {
            if (haystack.substring(i, i + m) == needle) {
                return i
            }
        }
        
        -1
    }
}