class Solution {
    fun permuteUnique(nums: IntArray): List<List<Int>> {
        nums.sort()
        val result = mutableListOf<List<Int>>()
        val current = mutableListOf<Int>()
        val used = BooleanArray(nums.size)
        
        fun backtrack() {
            if (current.size == nums.size) {
                result.add(ArrayList(current))
                return
            }
            
            for (i in nums.indices) {
                if (used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1])) {
                    continue
                }
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