# @param {Integer[]} nums
# @return {Integer}
def max_sub_array(nums)
    max_sum = current_sum = nums[0]
    (1...nums.length).each do |i|
        current_sum = [nums[i], current_sum + nums[i]].max
        max_sum = [max_sum, current_sum].max
    end
    max_sum
end