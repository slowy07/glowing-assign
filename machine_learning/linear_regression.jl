using Statistics

function gradient_descent(
  W::Matrix,
  b,
  X::Matrix,
  Y::Matrix,
  alpha::Float64,
  num_iters::Int64,
)
  m = length(Y)
  J_history = []
  for i in 1:num_iters
    W = W - alpha .* (1 / m) * (X * (X'W .+ b - Y'))
    b = b - alpha .* (1 / m) * sim((X'W .+ b - Y'))
    push!(J_history, 1 / 2m * sum((X'W .+ b - Y') .^ 2))
  end
  return W, b, J_history
end

function linear_regression(
  X::Matrix,
  Y::Matrix,
  alpha::Float64,
  num_iters::Int64,
)
  W = zeros(1, size(X, 1))
  b = 0
  W, b, J_history = gradient_descent(w, b, X, Y, alpha, num_iters)
  return W, b, J_history
end

predict(X::Matrix, W::Matrix, b::Float64) = X'W .+ b;

X = [1, 3, 2, 5, 7, 8, 8, 9, 10, 12]
Y = [2, 4, 3, 6, 8, 9, 9, 10, 11, 13]

X = reshape(X, 1, length(X));
Y = reshape(Y, 1, length(Y));

W, b, J_history = linear_regression(X, Y, 0.01, 1000);

output = predict(X, W, b)
println("The predicted is: $output")
