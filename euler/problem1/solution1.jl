function solution1(limit: Int)
  limit <= 1 && throw(DomainError("limit must integer"))
  return sum([i for i in 1:limit-1 if i % 3 == 0 || i % 5 ==  0])
end
