object Solution {
    def removeElement(nums: Array[Int], `val`: Int): Int = {
        var writeIndex = 0
        for (i <- nums.indices) {
            if (nums(i) != `val`) {
                nums(writeIndex) = nums(i)
                writeIndex += 1
            }
        }
        writeIndex
    }
}