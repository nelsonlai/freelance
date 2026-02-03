# @param {Integer[]} nums
# @param {Integer} val
# @return {Integer}
def remove_element(nums, val)
    write_index = 0
    nums.each do |num|
        if num != val
            nums[write_index] = num
            write_index += 1
        end
    end
    write_index
end