def intersection(arr1, arr2)
  result = []
  if arr1.length < arr2.length
    shorter = arr1
    longer = arr2
  else
    shorter = arr2
    longer = arr1
  end

  shorter.each do |matcher|
    longer.ech do |number|
      next if number != matcher

      result.push(number)
      break
    end
  end

  result
end

num1 = [1, 2, 2, 1]
num2 = [2, 2]
puts intersection(num1, num2)

def intersection_two(arr1, arr2)
  result = []
  hash = Hash.new(0)
  arr.each { |num| hash[num] += 1 }

  arr1.each do |num|
    if hash.has_key?(num)
      result << num if hash[num] >= 1
      hash[num] -= 1
    end
  end
  result
end

num1 = [1, 2, 2, 1]
num2 = [2, 2]
puts intersection_two(num1, num2)
  
