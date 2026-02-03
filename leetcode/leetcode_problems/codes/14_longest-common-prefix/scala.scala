object Solution {
    def longestCommonPrefix(strs: Array[String]): String = {
        if (strs.isEmpty) {
            return ""
        }
        
        for (i <- strs(0).indices) {
            val char = strs(0)(i)
            for (j <- 1 until strs.length) {
                if (i >= strs(j).length || strs(j)(i) != char) {
                    return strs(0).substring(0, i)
                }
            }
        }
        
        strs(0)
    }
}