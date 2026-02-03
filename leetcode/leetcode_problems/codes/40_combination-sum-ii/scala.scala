import scala.collection.mutable

object Solution {
    def combinationSum2(candidates: Array[Int], target: Int): List[List[Int]] = {
        val sorted = candidates.sorted
        val result = mutable.ListBuffer[List[Int]]()
        val path = mutable.ListBuffer[Int]()
        
        def backtrack(start: Int, remaining: Int): Unit = {
            if (remaining == 0) {
                result += path.toList
                return
            }
            if (remaining < 0) {
                return
            }
            
            for (i <- start until sorted.length) {
                if (i > start && sorted(i) == sorted(i - 1)) {
                    // skip duplicates
                } else {
                    path += sorted(i)
                    backtrack(i + 1, remaining - sorted(i))
                    path.remove(path.length - 1)
                }
            }
        }
        
        backtrack(0, target)
        result.toList
    }
}