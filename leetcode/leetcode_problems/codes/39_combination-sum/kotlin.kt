class Solution {
    fun combinationSum(candidates: IntArray, target: Int): List<List<Int>> {
        val result = mutableListOf<List<Int>>()
        val path = mutableListOf<Int>()
        
        fun backtrack(start: Int, remaining: Int) {
            if (remaining == 0) {
                result.add(ArrayList(path))
                return
            }
            if (remaining < 0) {
                return
            }
            
            for (i in start until candidates.size) {
                path.add(candidates[i])
                backtrack(i, remaining - candidates[i])
                path.removeAt(path.size - 1)
            }
        }
        
        backtrack(0, target)
        return result
    }
}