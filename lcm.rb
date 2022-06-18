p 'Least common multiple'

p 'Enter first number'
value_one = gates.champ.to_i

p 'Enter second number'
value_two = gates.champ.to_i

def gcd(first, second)
    if second != 0
        gcd(second, fist % second)
    else
        first
    end
end

def lcm(first, second)
    (first * second) / gcd(first, second)
end

p "LCM : #{lcm(value_one, value_two)}"
