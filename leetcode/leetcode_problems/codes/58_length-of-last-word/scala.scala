object Solution {
    def lengthOfLastWord(s: String): Int = {
        val trimmed = s.trim
        var length = 0
        for (i <- trimmed.length - 1 to 0 by -1) {
            if (trimmed(i) == ' ') {
                return length
            }
            length += 1
        }
        length
    }
}