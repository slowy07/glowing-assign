def add(*array)
    sum = 0
    array.each {|a| sum += a}
    puts "The sum of following elements #{array} is #{sum}"

rescue StandardError
    puts 'Error: Please provide number only'
end

puts add(1)
puts add(2, 5, -4)
puts add(25, 45)
