class Abs
    def self.call(number)
        return -number if number.negative?
        number
    end
end