def abs_max(x, y)
    num = x - y
    max_value = ((x + y + num.abs) / 2)
    "the abs max #{x} and #{y} is #{max_value}"
rescue StandardError
    'Error: Provide number only'
end

puts abs_max(10, 20)
