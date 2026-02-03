def max_subarray_sum(nums):
    max_so_far = float('-inf')
    max_ending_here = 0
    start = end = temp_start = 0

    for i, num in enumerate(nums):
        max_ending_here += num

        if max_ending_here > max_so_far:
            max_so_far = max_ending_here
            start = temp_start
            end = i

        if max_ending_here < 0:
            max_ending_here = 0
            temp_start = i + 1

    return max_so_far, nums[start:end+1]

# Example usage
nums = [-2, 9, -3, 2, -4, -2, 1, 2, 12, -3]
max_sum, subarray = max_subarray_sum(nums)

print("Maximum Subarray Sum:", max_sum)
print("Subarray:", subarray)