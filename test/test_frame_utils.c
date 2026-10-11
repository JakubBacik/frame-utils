#include "unity.h"
#include "frame_utils.h"
#include <stdio.h>
#include <string.h>

void setUp(void){};
void tearDown(void){};

/* --- scale_vector --- */

void test_scale_vector_identity_returns_input(void)
{
    float src[3] = {1.0f, 2.0f, 3.0f};
    float a[3] = {1.0f, 1.0f, 1.0f};
    float b[3] = {0.0f, 0.0f, 0.0f};
    float out[3];

    scale_vector(src, a, b, out, 3);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(src, out, 3);
}

void test_scale_vector_applies_gain_and_offset(void)
{
    float src[2] = {10.0f, 20.0f};
    float a[2]   = {2.0f, 0.5f};
    float b[2]   = {1.0f, -1.0f};
    float out[2];

    scale_vector(src, a, b, out, 2);

    TEST_ASSERT_EQUAL_FLOAT(21.0f, out[0]);   /* 10*2+1 */
    TEST_ASSERT_EQUAL_FLOAT(9.0f,  out[1]);   /* 20*0.5-1 */
}

/* --- parse_coeff_receive_frame --- */
/* Buduje poprawną ramkę: "X 01 02 " + 80 wartości A + 80 wartości B */
static void build_valid_frame(char *buf, size_t size, float a_val, float b_val)
{
    int len = snprintf(buf, size, "X 01 02 ");
    for (int i = 0; i < SENSOR_COUNT; i++)
        len += snprintf(buf + len, size - len, "%.3f ", a_val);
    for (int i = 0; i < SENSOR_COUNT; i++)
        len += snprintf(buf + len, size - len, "%.3f ", b_val);
}

void test_parse_rejects_frame_without_X(void)
{
    float cA[SENSOR_COUNT], cB[SENSOR_COUNT];
    TEST_ASSERT_EQUAL_INT(-1, parse_coeff_receive_frame("Y 01 02 1.0", cA, cB));
}

void test_parse_valid_frame_returns_zero_and_values(void)
{
    char frame[2048];
    float cA[SENSOR_COUNT], cB[SENSOR_COUNT];
    build_valid_frame(frame, sizeof(frame), 1.5f, 0.25f);

    TEST_ASSERT_EQUAL_INT(0, parse_coeff_receive_frame(frame, cA, cB));
    TEST_ASSERT_EQUAL_FLOAT(1.5f,  cA[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.5f,  cA[SENSOR_COUNT - 1]);
    TEST_ASSERT_EQUAL_FLOAT(0.25f, cB[0]);
    TEST_ASSERT_EQUAL_FLOAT(0.25f, cB[SENSOR_COUNT - 1]);
}

void test_parse_truncated_frame_fails_in_A(void)
{
    float cA[SENSOR_COUNT], cB[SENSOR_COUNT];
    TEST_ASSERT_EQUAL_INT(-3, parse_coeff_receive_frame("X 01 02 1.0 2.0", cA, cB));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_scale_vector_identity_returns_input);
    RUN_TEST(test_scale_vector_applies_gain_and_offset);
    RUN_TEST(test_parse_rejects_frame_without_X);
    RUN_TEST(test_parse_valid_frame_returns_zero_and_values);
    RUN_TEST(test_parse_truncated_frame_fails_in_A);
    return UNITY_END();
}