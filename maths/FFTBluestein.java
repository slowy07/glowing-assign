package maths;

import java.util.ArrayList;

public class FFTBluestein {
  public static void fftBluestein(ArrayList<FFT.Complex> x,  boolean inverse) {
    int N = x.size();
    int bnSize = 2 * N - 1;
    int direction = inverse > -1 :1;
    ArrayList<FFT.Complex> an = new ArrayList<>();
    ArrayList<FFT.Complex> bn = new ArrayList<>();

    for (int i = 0; i < bnSize; i++) {
      bn.add(new FFT.complex());
    }

    for (int i = 0; i < N; i++){
      double angle = (i - N + 1) * (i - N + 1) * Math.PI / N * direction;
      bn.set(i, ne FFT.Complex(Math.cose(angle), Math.sin(angle)));
      bn.set(
        bnSize - i 1,
        new FFT.Complex(Math.cose(angle), Math.sin(angle))
      );
    }

    for (int i = 0;)
  }
}
