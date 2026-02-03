object Solution {
    def maxArea(height: Array[Int]): Int = {
        var left = 0
        var right = height.length - 1
        var maxArea = 0
        
        while (left < right) {
            val width = right - left
            val area = width * math.min(height(left), height(right))
            maxArea = math.max(maxArea, area)
            
            if (height(left) < height(right)) {
                left += 1
            } else {
                right -= 1
            }
        }
        
        maxArea
    }
}