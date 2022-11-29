def armstrong_number(number)
  num = number
  sum = 0
  len = number.digits.count
  while number != 0
    remainder = number % 10
    sum += remainder ** len
    number /= 10
  end
  if num == sum
    "number #{num} are amstrong number"
  else
    "number #{num} not armstrong number"
rescue StandarError
  "error: provide number only"
end


puts armstrong_number(153)

