package maths;

class DigitalRoot{
  public static int digitalRoot(int n) {
    if (single(n) <= 9) {
      return single(n);
    } else {
      return digitalRoot(single(n));
    }
  }

  public static int single(int n) {
    if (n <= 9) {
      return n;
    } else {
      return (n % 10) + single(n / 10);
    }
  }
}
