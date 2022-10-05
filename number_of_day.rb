require 'date'

def number_of_days(date1, date2)
    beginning_date = Date.parse(date1)
    end_date = Date.parse(date2)
    (end_date - beginning_date).to_i.abs
end

puts number_of_days('2019-06-29', '2019-06-30')
