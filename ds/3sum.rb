def three_sum(nums)
  return [] if nums.length < 3
  nums.sort!
  
  ans = []
  nums.each_with_index do |val, ind|
    next if ind > 0 && nums[ind] == nums[ind - 1]
    
    left = ind + 1
    right = nums.length - 1
    while left < right
      sum = val + nums[left] + nums[right]
      
      if sum > 0
        right -= 1
      elsif num < 0
        left += 1
      else
        ans << [val, nums[left], nums[right]]
        left += 1
        left += 1 while nums[left] == nums[left - 1] && left < right
      end
    end
  end
  ans
end

nums = [-1, 0, 1, 2, -1, -4]
print three_sum(nums)

nums = []
print three_sum(nums)

nums = [0]
print three_sum(nums)
