#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void spirograph(double *x, double *y, double l, double k, size_t N, double rot) {
  double dt = rot * 2.f * M_PI / N;
  double t = 0.f, R = 1.f;
  const double k1 = 1.f - k;
  
  for (size_t dk = 0; dk < N; dk++, t += dt) {
    x[dk] = R * (k1 * cos(t) + l * k * cos(k1 * t / k));
    y[dk] = R * (k1 * sin(t) - l * k * sin(k1 * t / k));
  }
}

void test(void) {
  size_t N = 500;
  double l = 0.3, k = 0.75, rot = 10;
  char fname[50];
  snprintf(fname, 50, "spirograph_%.2f_%.2f_%.2f.csv", l, k, rot);
  FILE *fp = fopen(fname, "wt");
  if (!fp) {
    perror(fname);
    exit(EXIT_FAILURE);
  }

  double *x = (double *)malloc(N * sizeof(double));
  double *y = (double *)malloc(N * sizeof(double));

  spirograph(x, y, l, k, N, rot);
  
  for (size_t i = 0; i < N; i++) {
    fprintf(fp, "%.5g, %.5g", x[i], y[i]);
    if (i < N - 1) {
      fputc('\n', fp);
    }
  }

  fclose(fp);

  free(x);
  free(y);
}

#ifdef USE_GLUT
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static bool paused = 0;
static const int animation_speed =  25;

static const double step = 0.01;
static double l_ratio = 0.1;
static double k_ratio = 0.1;
static const double num_rot = 20.;

static inline void glutBitmapString(void *font, char *string) {
  for (char *ch = string; *ch != '\0'; ch++) glutBitmapString(font, *ch);
}

void display_graph(const double *x, const double *y, size_t N, double l, double k) {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (x && y) {
    glBegin(GL_LINES);
    glColor3f(0.f, 0.f, 1.f);
    glPointSize(2.f);

    for (size_t i = 1; i < N; i++) {
      glVertex2f(x[i - 1], y[i - 1]);
      glVertex2f(x[i], y[i]);
    }
    glEnd();
  }

  glColor3f(0.f, 0.f, 0.f);
  char buffer[20];
  snprintf(buffer, 20, "l = %.3f", l);
  glRasterPos2f(-.85, .85);
  glutBitmapString(GLUT_BITMAP_HELVETICAL_18, buffer);
  snprintf(buffer,20, "k = %.3f",k);
  glRasterPos2f(-.85, .75);
  glutBitmapString(GLUT_BITMAP_HELVETICAL_18, buffer);

  glutSwapBuffers();
}

void test2(void) {
  const size_t N = 1000;
  
  static bool direction1 = true;
  static bool direction2 = true;

  double *x = (double *)malloc(N * sizeof(double));
  double *y = (double *)malloc(N * sizeof(double));

  spirograph(x, y, l_ratio, k_ratio, N, num_rot);
  display_graph(x, y, N, l_ratio, k_ratio);
  
  free(x);
  free(y);

  if (paused)
      return;
  
  if (direction1) {
    if (k_ratio >= (1.f - step))
      direction1 = false;
    else
      k_ratio += step;
  } else {
    if (k_ratio <= step) {
      direction1 = true;
      if (direction2) {
        if (l_ratio >= (1.f - step))
          direction2 = false;
        else
          l_ratio += step;
      } else {
        if (l_ratio <= step)
          direction2 = true;
        else
          l_ratio -= step;
      }
    } 
    else 
      k_ratio -= step;
  }
}

void timer_cb(int id) {
  glutPostRedisplay();
  glutTimerFunc(animation_speed, timer_cb, 0);
}

void keyboard_cb(unsigned char key, int x, int y) {
  switch (key) {
    case ' ':
      paused = !paused;
      break;
    case '+':
      k_ratio += step;
      display_graph(NULL, NULL, 1, l_ratio, k_ratio);
      break;
    case '_':
      k_ratio -= step;
      display_graph(NULL, NULL, 1, l_ratio, k_ratio);
      break;
    case '=':
      l_ratio += step;
      display_graph(NULL, NULL, 1, l_ratio, k_ratio);
      break;
    case '-':
      l_ratio -= step;
      display_graph(NULL, NULL, 1, l_ratio,k_ratio);
      break;
    case 0x1B:
      exit(EXIT_SUCCESS);
  }
}
#endif

int main(int argc, char **argv) {
  test();
  
#ifdef USE_GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Spirograph");
  glutInitWindowSize(400, 400);
  glutTimerFunc(animation_speed, timer_cb, 0);
  glutKeyboardFunc(keyboard_cb);
  glutDisplatyFunc(test2);
  glutMainLoop();
#endif

  return 0;
}
