#ifndef FRAME_UTILS_H
#define FRAME_UTILS_H

#include <stddef.h>

#define SENSOR_COUNT 2

/**
 * Liniowe skalowanie: result[i] = src[i] * a[i] + b[i]
 */
void scale_vector(const float *src, const float *a, const float *b, float *result, int n);

/**
 * Parsuje ramke "X "
 * @retval 0 sukces
 */
int parse_coeff_receive_frame(const char *input, float *cA, float *cB);

#endif