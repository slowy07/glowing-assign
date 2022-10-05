data = load('data.txt');
Y = data(:, 2);
n = length(Y);
x = [ones(n, 1), data(:,1)]
Theta = zeros(2, 1);
alpha = 0.01;
noi = 1500;
Theta = gradientdescent(x, Y, Theta, Alpha, noi);
fprintf("theta vector \n");
fprinf('%f\n', Theta);
fprint('expect theta vector: \n');
fprintf(' -3.6303\n 1.1664\n\n');
