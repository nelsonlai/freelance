class Solution {
    fun longestCommonPrefix(strs: Array<String>): String {
        if (strs.isEmpty()) {
            return ""
        }
        
        for (i in strs[0].indices) {
            val char = strs[0][i]
            for (j in 1 until strs.size) {
                if (i >= strs[j].length || strs[j][i] != char) {
                    return strs[0].substring(0, i)
                }
            }
        }
        
        return strs[0]
    }
}