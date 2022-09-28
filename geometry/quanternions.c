#include <stdio.h>
#ifdef __arm__
#define LIBQUAT_ARM
#include <arm_math.h>
#else
#include <math.h>
#endif
#include <assert.h>
#include "geometry_datatypes.h"

/**
 * \f{eqnarray*}{
 * q_{0} & =
 * &\cos\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * +
 * \sin\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{1} & =
 * &\sin\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * -
 * \cos\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{2} & =
 * &\cos\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * +
 * \sin\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{3} & =
 * &\cos\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)
 * -
 * \sin\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)\\
 * \f}
 */

quanternion quat_from_euler(const euler *in_euler) {
  quanternion out_quat;

  if (!in_euler) {
    fprintf(stderr, "%s: Invalid input.", __func__);
    return out_quat;
  }

  quanternion temp;

  float cy = cosf(in_euler->yaw * 0.5f);
  float sy = sinf(in_euler->yaw * 0.5f);
  float cp = cosf(in_euler->pitch * 0.5f);
  float sp = sinf(in_euler->pitch * 0.5f);
  float cr = cosf(in_euler->roll * 0.5f);
  float sr = sinf(in_euler->roll * 0.5f);

  temp.w = cr * cp * cy + sr * sp * sy;
  temp.q1 = sr * cp * cy - cr * sp * sy;
  temp.q2 = cr * sp * cy + sr * cp * sy;
  temp.q3 = cr * cp * sy - sr * sp * cy;

  return temp;
}

/**
 * \f{eqnarray*}{
 * \phi & = &
 * \tan^{-1}\left[\frac{2\left(q_0q_1+q_2q_3\right)}{1-2\left(q_1^2+q_2^2\right)}\right]\\
 * \theta & =
 * &-\sin^{-1}\left[2\left(q_0q_2-q_3q_1\right)\right]\\
 * \psi & = &
 * \tan^{-1}\left[\frac{2\left(q_0q_3+q_1q_2\right)}{1-2\left(q_2^2+q_3^2\right)}\right]\\
 * \f}
 */
euler euler_from_quat(const quanternion *in_quat) {
  euler out_euler;
  if (!in_quat) {
    fprintf(stderr, "%s: Invalid input.", __func__);
    return out_euler;
  }

  out_euler.roll = atan2f(
    2.f * (in_quat->w * in_quat->q1 + in_quat->q2 * in_quat->q3),
    1.f - 2.f * (in_quat->q1 * in_quat->q1 + in_quat->q2 * in_quat->q2));
  out_euler.pitch = 
    asinf(2.f * (in_quat->w * in_quat->q2 + in_quat->q1 * in_quat->q3));
  out_euler.yaw = atan2f (
    2.f * (in_quat->w * in_quat->q3 + in_quat->q1 * in_quat->q2),
    1.f - 2.f * (in_quat->q2 * in_quat->q2 + in_quat->q3 * in_quat->q3));
  return out_euler;
}

/**
 * \f{eqnarray*}{
 * \mathbf{c} & = & \mathbf{a}\otimes\mathbf{b}\\
 * & = & \begin{bmatrix}a_{0} & a_{1} & a_{2} &
 *  a_{3}\end{bmatrix}\otimes\begin{bmatrix}b_{0} & b_{1} & b_{2} &
 *  b_{3}\end{bmatrix}\\
 * & = &
 * \begin{bmatrix}
 *  a_{0}b_{0}-a_{1}b_{1}-a_{2}b_{2}-a_{3}b_{3}\\
 *  a_{0}b_{1}+a_{1}b_{0}+a_{2}b_{3}-a_{3}b_{2}\\
 *  a_{0}b_{2}-a_{1}b_{3}+a_{2}b_{0}+a_{3}b_{1}\\
 *  a_{0}b_{3}+a_{1}b_{2}-a_{2}b_{1}+a_{3}b_{0}
 * \end{bmatrix}^{T}
 * \f}
 */
quanternion  quanternion_multiply(const quanternion *in_quat1,
  const quanternion  *in_quat2) {
  
  quanternion out_quat;
  if (!in_quat1 || in_quat2 )  {
    fprintf(stderr, "%s: Invalid output", __func__);
    return out_quat;
  }

  out_quat.w = in_quat1->w * in_quat2->w - in_quat1->q1 * in_quat2->q1 -
    in_quat1->q2 * in_quat2->q2 - in_quat1->q3 * in_quat2->q3;
  out_quat.q1 = in_quat1->w * in_quat2->q1 + in_quat1->q1 * in_quat2->w +
    in_quat1->q2 * in_quat2->q3 - in_quat1->q3 * in_quat2->q2;
  out_quat.q2 = in_quat1->w * in_quat2->q2 - in_quat1->q1 * in_quat2->q3 +
    in_quat1->q2 * in_quat2->w + in_quat1->q3 * in_quat2->q1;
  out_quat.q3 = in_quat1->w * in_quat2->q3 + in_quat1->q1 * in_quat2->q2 -
    in_quat1->q2 * in_quat2->q1 + in_quat1->q3 * in_quat2->w;

  return out_quat;
}

static void test() {
  quanternion quat = {0.7071f, 0.7071f, 0.f, 0.f};
  euler eul = euler_from_quat(&quat);
  printf("Euler: %.4g, %.4g, %.4g\n", eul.pitch, eul.roll, eul.yaw);

  quanternion test_quat = quat_from_euler(&eul);
  printf("quanternion: %.4g %+.4g %+.4g %+.4g\n", test_quat.w,
      test_quat.dual.x, test_quat.dual.y, test_quat.dual.z);

  assert(fabsf(test_quat.w - quat.w) < .01);
  assert(fabsf(test_quat.q1 - quat.q1) < .01);
  assert(fabsf(test_quat.q2 - quat.q2) < .01);
  assert(fabsf(test_quat.q3 - quat.q3) < .01);
}

int main() {
  test();
  return 0;
}
