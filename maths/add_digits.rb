def add_digits(num)
    return 0 if num == 0
    return 9 if num % 9 == 0
    num % 9
end

puts(add_digits(38))
