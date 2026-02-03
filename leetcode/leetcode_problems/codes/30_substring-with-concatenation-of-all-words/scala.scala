import scala.collection.mutable

object Solution {
    def findSubstring(s: String, words: Array[String]): List[Int] = {
        val result = mutable.ListBuffer[Int]()
        if (s.isEmpty || words.isEmpty) {
            return result.toList
        }
        
        val wordLen = words(0).length
        val wordCount = mutable.Map[String, Int]()
        words.foreach { word =>
            wordCount(word) = wordCount.getOrElse(word, 0) + 1
        }
        
        for (i <- 0 until wordLen) {
            var left = i
            val seen = mutable.Map[String, Int]()
            var count = 0
            
            var j = i
            while (j <= s.length - wordLen) {
                val word = s.substring(j, j + wordLen)
                
                if (wordCount.contains(word)) {
                    seen(word) = seen.getOrElse(word, 0) + 1
                    count += 1
                    
                    while (seen(word) > wordCount(word)) {
                        val leftWord = s.substring(left, left + wordLen)
                        seen(leftWord) -= 1
                        count -= 1
                        left += wordLen
                    }
                    
                    if (count == words.length) {
                        result += left
                        val leftWord = s.substring(left, left + wordLen)
                        seen(leftWord) -= 1
                        count -= 1
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
        
        result.toList
    }
}