class Ceil
    class << self
        def call(number)
            return number if number.is_a?(integer) || number == number.to_i

            number.to_i + 1
        end
    end
end
