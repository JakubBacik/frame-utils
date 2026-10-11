#include "frame_utils.h"
#include <stdlib.h>

void scale_vector(const float *src, const float *a, const float *b,
                  float *result, int n)
{
    for (int i = 0; i < n; i++) {
        result[i] = (src[i] * a[i]) + b[i];
    }
}

int parse_coeff_receive_frame(const char *input, float *cA, float *cB)
{
    char *end;
    const char *ptr = input;

    if (*ptr != 'X')
        return -1;

    ptr += HEADER_SKIP;

    for (int i = 0; i < SENSOR_COUNT; i++) {
        cA[i] = strtof(ptr, &end);
        if (ptr == end) return -2;
        ptr = end;
    }

    for (int i = 0; i < SENSOR_COUNT; i++) {
        cB[i] = strtof(ptr, &end);
        if (ptr == end) return -3;
        ptr = end;
    }
    return 0;
}