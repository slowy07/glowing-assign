function retval = linear_diopathine_eqn (a, b, c)
  if mod(c, gcd(a, b)) == 0
    retval = true;
  else
    retval = false;
end
