p 'Least Common Multiple'

p 'Enter first number'
value_one = gets.chomp.to_i

p 'Second number'
value_one = gets.chomp.to_i

def gcd(first, second)
  if second != 0
    gcd(second, first % second)
  else
    first
  end
end

def lcm(first, second)
  (first * second) / gcd(first, second)
end

p "LCM: #{lcm(value_one, value_two)}"
