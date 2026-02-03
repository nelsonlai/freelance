class Solution {
    fun lengthOfLastWord(s: String): Int {
        val trimmed = s.trimEnd()
        var length = 0
        for (i in trimmed.length - 1 downTo 0) {
            if (trimmed[i] == ' ') {
                break
            }
            length++
        }
        return length
    }
}