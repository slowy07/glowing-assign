function Theta = gradientdescent(x, Y, Theta, Alpha, noi)
  n = length(Y);
  for i = 1:noi
    theta_1 = Theta(1) - Alpha * (1 / n) * sum(((x * Theta) - Y) . * x(:, 1)); 
    theta_2 = Theta(2) - Alpha * (1 / n) * sum(((x * Theta) - Y) . * x(:, 2));
    
    Theta(1) = theta_1;
    Theta(2) = theta_2;
  end
end
