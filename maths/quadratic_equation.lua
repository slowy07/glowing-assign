return function(
  p,
  q
)
  local root = (p ^ 2 / 4 - q) ^ 0.5
  if root ~= root then
    return
  end
  local x_1, x_2 = -p / 2 - root, -p / 2 + root
  if x_1 == x_2 then
    return x_1
  end

  return x_1, x_2
end
