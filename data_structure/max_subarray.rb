def max_subarray(nums)
  max_sum = nums[0]
  return max_sum if nums.length == 1

  current_sum = 0
  nums.each do |num|
    current_sum = 0 if current_sum < 0
    current_sum += num
    
    max_sum = [max_sum, current_sum].max
  end
  max_sum
end

nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

print max_subarray(nums)
nums = [1]
print max_subarray(nums)
