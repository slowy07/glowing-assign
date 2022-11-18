def add_digits(num)
  return num if num.to_s.length < 2

  digits_to_sum = num.to_s.split('')
  sum = 0
  digits_to_sum.each do |num|
    sum += num.to_i
  end
  add_digits(sum)
end

puts(add_digits(38))
