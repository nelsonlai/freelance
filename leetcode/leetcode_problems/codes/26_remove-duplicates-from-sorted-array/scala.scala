object Solution {
    def removeDuplicates(nums: Array[Int]): Int = {
        if (nums.isEmpty) {
            return 0
        }
        
        var writeIndex = 1
        for (i <- 1 until nums.length) {
            if (nums(i) != nums(i - 1)) {
                nums(writeIndex) = nums(i)
                writeIndex += 1
            }
        }
        
        writeIndex
    }
}