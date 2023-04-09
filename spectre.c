#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#define N 256  

int main(int argc, char *argv[]) {
  double data[N];
  fftw_complex out[N];
  fftw_plan p;

  FILE *audioFile = fopen("audio.wav", "r");
  fread(data, sizeof(double), N, audioFile);
  fclose(audioFile);

  p = fftw_plan_dft_r2c_1d(N, data, out, FFTW_ESTIMATE);

  fftw_execute(p);

  for (int i = 0; i < N/2; i++) {
    double magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    printf("Fréquence: %d Hz, Magnitude: %f\n", i, magnitude);
  }

  fftw_destroy_plan(p);

  return 0;
}
