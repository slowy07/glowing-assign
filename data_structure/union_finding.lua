local union_find = {}

function union_find.new()
  return {}
end

function union_find:make_set(elem)
  assert(not self[elem], "element already exists")
  self[elem] = {elem}
end

function union_find:union(rep_1, rep_2)
  local larger_set, smaller_set = self[rep_1], self[rep_2]
  if larger_set == smaller_set then
    return
  end
  if #larger_set < #smaller_set then
    larger_set, smaller_set = smaller_set, larger_set
  end
  
  for _, elem in ipairs(smaller_set) do
    table.insert(larger_set, elem)
    self[elem] = larger_set
  end
end

function union_find:find(elem)
  return assert(self[elem], "element doesnt exists")[1]
end

return require("class")(union_find)
