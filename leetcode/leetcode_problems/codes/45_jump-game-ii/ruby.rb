# @param {Integer[]} nums
# @return {Integer}
def jump(nums)
    jumps = 0
    current_end = 0
    farthest = 0
    
    (0...nums.length - 1).each do |i|
        farthest = [farthest, i + nums[i]].max
        if i == current_end
            jumps += 1
            current_end = farthest
        end
    end
    
    jumps
end