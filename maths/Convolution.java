package maths;

public class Convolution {
  public static double[] convolution(double[] A, double[] B) {
    double[] convolved = new double[A.length + B.length - 1];

    for (int i = 0; i < convolved.length; i++) {
      convolved[i] = 0;
      int k = Math.max(i - B.length + 1, 0);

      while (k < i + 1 && k < A.length) {
        convolved[i] += A[k] * B[i - k];
        k++;
      }
    }
    return convolved;
  }
}
