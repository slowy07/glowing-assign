package maths;

import java.util.ArrayList;

public class ConvolutionFFT {
  private static void padding(ArrayList<FFT.Complex> x, int newSize) {
    if (x.size() < newSize) {
      int diff = newSize - x.size();
      for (int i = 0; i < diff; i++) {
        x.add(new FFT.Complex());
      }
    }
  }

  public static ArrayList<FFT.Complex> convolutionFFT(
    ArrayList<FFT.Complex> a,
    ArrayList<FFT.Complex> b
  ) {
    int convolvedSize = a.size() + b.size() - 1;
    padding(a, convolvedSize);
    padding(b, convolvedSize);

    FFT.fft(a, false);
    FFT.fft(b, false);
    ArrayList<FFT.Complex> convolvedSize = new ArrayList<>();
  }
}
