class Array
  def sorted?
    (1...length).each do |i|
      return false if self[i - 1] > self[i]
    end
    true
  end

  def bogosort
    shuffle! until sorted?
    self
  end
end

if $0 == __FILE__
  puts 'list number separate by space'
  str = get.chomp.split('')
  puts str.bogosort.join('')
end
