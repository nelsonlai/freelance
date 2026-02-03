class Solution {
    fun permute(nums: IntArray): List<List<Int>> {
        val result = mutableListOf<List<Int>>()
        val current = mutableListOf<Int>()
        val used = BooleanArray(nums.size)
        
        fun backtrack() {
            if (current.size == nums.size) {
                result.add(ArrayList(current))
                return
            }
            
            for (i in nums.indices) {
                if (used[i]) continue
                used[i] = true
                current.add(nums[i])
                backtrack()
                current.removeAt(current.size - 1)
                used[i] = false
            }
        }
        
        backtrack()
        return result
    }
}