# @param {Integer[]} nums
# @return {Integer}
def first_missing_positive(nums)
    n = nums.length
    
    # Place each number in its correct position
    i = 0
    while i < n
        num = nums[i]
        if num >= 1 && num <= n && nums[num - 1] != num
            nums[i], nums[num - 1] = nums[num - 1], nums[i]
        else
            i += 1
        end
    end
    
    # Find the first missing positive
    (0...n).each do |i|
        return i + 1 if nums[i] != i + 1
    end
    
    n + 1
end