class Solution {
    fun findSubstring(s: String, words: Array<String>): List<Int> {
        val result = mutableListOf<Int>()
        if (s.isEmpty() || words.isEmpty()) {
            return result
        }
        
        val wordLen = words[0].length
        val wordCount = mutableMapOf<String, Int>()
        for (word in words) {
            wordCount[word] = wordCount.getOrDefault(word, 0) + 1
        }
        
        for (i in 0 until wordLen) {
            var left = i
            val seen = mutableMapOf<String, Int>()
            var count = 0
            
            var j = i
            while (j <= s.length - wordLen) {
                val word = s.substring(j, j + wordLen)
                
                if (wordCount.containsKey(word)) {
                    seen[word] = seen.getOrDefault(word, 0) + 1
                    count++
                    
                    while (seen[word]!! > wordCount[word]!!) {
                        val leftWord = s.substring(left, left + wordLen)
                        seen[leftWord] = seen[leftWord]!! - 1
                        count--
                        left += wordLen
                    }
                    
                    if (count == words.size) {
                        result.add(left)
                        val leftWord = s.substring(left, left + wordLen)
                        seen[leftWord] = seen[leftWord]!! - 1
                        count--
                        left += wordLen
                    }
                } else {
                    seen.clear()
                    count = 0
                    left = j + wordLen
                }
                j += wordLen
            }
        }
        
        return result
    }
}