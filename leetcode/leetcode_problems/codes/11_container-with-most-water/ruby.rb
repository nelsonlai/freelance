# @param {Integer[]} height
# @return {Integer}
def max_area(height)
    left, right = 0, height.length - 1
    max_area = 0
    
    while left < right
        width = right - left
        area = width * [height[left], height[right]].min
        max_area = [max_area, area].max
        
        if height[left] < height[right]
            left += 1
        else
            right -= 1
        end
    end
    
    max_area
end