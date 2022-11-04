function simpson_integration(f::Function, a::Real, b::Real, n::Int)
    Δₓ = (b - a) / n
    a₁(i) = 2i - 2
    a₂(i) = 2i - 1

    Σ = sum(1:(n/2)) do i
        return f(a + a₁(i) * Δₓ) + 4f(a + a₂(i) * Δₓ) + f(a + 2i * Δₓ)
    end

    return (Δₓ / 3) * Σ
end

result = simpson_integration(x -> 4 / (1 + x^2), 0, 1, 100_000)
result2 = simpson_integration(x -> 4 / (1 + x^2), 0, 1, 100_000) ≈ pi

println("res: $result")
println("res: $result2")
