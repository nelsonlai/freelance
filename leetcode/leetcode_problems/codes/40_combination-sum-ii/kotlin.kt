class Solution {
    fun combinationSum2(candidates: IntArray, target: Int): List<List<Int>> {
        candidates.sort()
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
                if (i > start && candidates[i] == candidates[i - 1]) {
                    continue
                }
                path.add(candidates[i])
                backtrack(i + 1, remaining - candidates[i])
                path.removeAt(path.size - 1)
            }
        }
        
        backtrack(0, target)
        return result
    }
}