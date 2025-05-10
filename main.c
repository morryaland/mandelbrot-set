#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>
#include <SDL3/SDL.h>

#define ITER 600
#define XMIN -2.2
#define XMAX 1.0
#define YMIN -1.2
#define YMAX 1.2

int main()
{
  SDL_Window *wind = SDL_CreateWindow("fractal", 800, 600, 0);
  SDL_Surface *screen = SDL_GetWindowSurface(wind);
  SDL_ShowWindow(wind);
  SDL_ClearSurface(screen, 0, 0, 0, 0xFF);
  double x = XMIN;
  double dx = (XMAX - XMIN) / 800.0;
  double y = YMIN;
  double dy = (YMAX - YMIN) / 600.0;
  for (int i = 0; i < 600; i++) {
    x = XMIN;
    for (int j = 0; j < 800; j++) {
      double x34 = x - 0.25;
      double p = sqrt((x - 0.25) * (x - 0.25) + y * y);
      double pc = 0.5 - 0.5 * cos(atan2(y, x - 0.25));
      if (p <= pc)
        goto next;
      double complex c = x + I * y;
      double complex z = 0;
      int n = 0;
      for (; cabs(z) < 2.0 && n < ITER; n++) {
        z = cpow(z, 2) + c;
      }
      if (n == ITER)
        goto next;
      SDL_WriteSurfacePixel(screen, j, i, 0xFF, 0xFF, 0xFF, 0xFF);
next:
      x += dx;
    }
    y += dy;
  }
  SDL_UpdateWindowSurface(wind);
  getchar();
}
