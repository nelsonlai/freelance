import scala.collection.mutable

object Solution {
    def combinationSum(candidates: Array[Int], target: Int): List[List[Int]] = {
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
            
            for (i <- start until candidates.length) {
                path += candidates(i)
                backtrack(i, remaining - candidates(i))
                path.remove(path.length - 1)
            }
        }
        
        backtrack(0, target)
        result.toList
    }
}