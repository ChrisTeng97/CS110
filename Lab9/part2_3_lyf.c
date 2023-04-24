#include <emmintrin.h> /* header file for the SSE intrinsics */
#include <time.h>
#include <stdio.h>

float **a;
float **b;
float **c;
float **c2;

int n = 40000;
int p = 20000;

void init(void) {
    a = malloc(n * sizeof(float *));
    b = malloc(4 * sizeof(float *));
    c = malloc(n * sizeof(float *));
    c2 = malloc(n * sizeof(float *));
    for (int i = 0; i < n; ++i) {
        a[i] = malloc(4 * sizeof(float));
        c[i] = malloc(p * sizeof(float));
        c2[i] = malloc(p * sizeof(float));
    }
    for (int i = 0; i < 4; ++i) {
        b[i] = malloc(p * sizeof(float));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[i][j] = (float) rand() / (float) RAND_MAX;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < p; ++j) {
            b[i][j] = (float) rand() / (float) RAND_MAX;
        }
    }
}

void check_correctness(char *msg) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            if (c[i][j] != c2[i][j]) {
                printf("%s incorrect!\n", msg);
                return;
            }
        }
    }
}

void naive_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // c = a * b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("naive: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
}

void loop_unroll_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // c2 = a * b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            c2[i][j] = 0;
            c2[i][j] += a[i][0] * b[0][j];
            c2[i][j] += a[i][1] * b[1][j];
            c2[i][j] += a[i][2] * b[2][j];
            c2[i][j] += a[i][3] * b[3][j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("unroll: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("loop_unroll_matmul");
}

void simd_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // c2 = a * b
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < p; j += 4){
            __m128 c_val = _mm_setzero_ps();
            for (int k = 0; k < 4; ++k){
                __m128 a_row = _mm_set1_ps(a[i][k]);
                __m128 b_col = _mm_loadu_ps(&b[k][j]);
                c_val = _mm_add_ps(c_val, _mm_mul_ps(a_row, b_col));
            }
            _mm_storeu_ps(&c2[i][j], c_val);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("simd: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("simd_matmul");
}

void loop_unroll_simd_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // c2 = a * b
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < p; j += 4){
            __m128 c_val = _mm_setzero_ps();
            __m128 a_row = _mm_set1_ps(a[i][0]);
            __m128 b_col = _mm_loadu_ps(&b[0][j]);
            c_val = _mm_add_ps(c_val, _mm_mul_ps(a_row, b_col));

            a_row = _mm_set1_ps(a[i][1]);
            b_col = _mm_loadu_ps(&b[1][j]);
            c_val = _mm_add_ps(c_val, _mm_mul_ps(a_row, b_col));

            a_row = _mm_set1_ps(a[i][2]);
            b_col = _mm_loadu_ps(&b[2][j]);
            c_val = _mm_add_ps(c_val, _mm_mul_ps(a_row, b_col));
            
            a_row = _mm_set1_ps(a[i][3]);
            b_col = _mm_loadu_ps(&b[3][j]);
            c_val = _mm_add_ps(c_val, _mm_mul_ps(a_row, b_col));
            
            _mm_storeu_ps(&c2[i][j], c_val);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("unroll+simd: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("loop_unroll_simd_matmul");
}


int main(void) {
    init();

    naive_matmul();
    simd_matmul();
    loop_unroll_matmul();
    loop_unroll_simd_matmul();

    return 0;
}

