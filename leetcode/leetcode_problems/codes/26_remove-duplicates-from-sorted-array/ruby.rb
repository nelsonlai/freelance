# @param {Integer[]} nums
# @return {Integer}
def remove_duplicates(nums)
    return 0 if nums.empty?
    
    write_index = 1
    (1...nums.length).each do |i|
        if nums[i] != nums[i - 1]
            nums[write_index] = nums[i]
            write_index += 1
        end
    end
    
    write_index
end