def twoSum(nums, target):
    num_map = {}  # key: number, value: index
    for i in range(len(nums)):
        complement = target - nums[i]
        if complement in num_map:
            return [num_map[complement], i]
        num_map[nums[i]] = i
    return []


def twoSum_slow(self, nums, target):
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]

    return []

print(twoSum([15, 2, 11, 7], 9))  # Output: [1, 3]

print(twoSum([3, 2, 4], 6))