# @param {Integer[]} nums
# @return {Boolean}
def can_jump(nums)
    farthest = 0
    nums.each_with_index do |num, i|
        return false if i > farthest
        farthest = [farthest, i + num].max
        return true if farthest >= nums.length - 1
    end
    true
end