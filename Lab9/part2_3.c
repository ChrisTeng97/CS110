#include <emmintrin.h> /* header file for the SSE intrinsics */
#include <time.h>
#include <math.h>
#include <stdio.h>

float **a;
float **b;
float **c;
float **c2;

int n = 40000;
int p = 20000;

void init(void) {
    // A: n*4; B: 4*p; res: C&C2: n*p.
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
            if (fabsf(c[i][j] - c2[i][j]) > 1e-6) {
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
    // TODO: implement me!
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("unroll: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("loop_unroll_matmul");
}

void simd_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // c2 = a * b
    // TODO: implement me!
    



    __m128 row1, row2, row3, row4;
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < p; j += 4) {
            row1 = _mm_setzero_ps();
            row2 = _mm_setzero_ps();
            row3 = _mm_setzero_ps();
            row4 = _mm_setzero_ps();
            for (int k = 0; k < 4; k++) {
                __m128 bvec = _mm_load_ps(b[k + j]);
                row1 = _mm_add_ps(row1, _mm_mul_ps(_mm_set1_ps(a[i * 4][k]), bvec));
                row2 = _mm_add_ps(row2, _mm_mul_ps(_mm_set1_ps(a[(i + 1) * 4 ][ k]), bvec));
                row3 = _mm_add_ps(row3, _mm_mul_ps(_mm_set1_ps(a[(i + 2) * 4 ][ k]), bvec));
                row4 = _mm_add_ps(row4, _mm_mul_ps(_mm_set1_ps(a[(i + 3) * 4 ][ k]), bvec));
            }
            _mm_store_ps(c2 [ i * 4 + j], row1);
            _mm_store_ps(c2 [ (i + 1) * 4 + j], row2);
            _mm_store_ps(c2 [ (i + 2) * 4 + j], row3);
            _mm_store_ps(c2 [ (i + 3) * 4 + j], row4);
        }
    }



    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            __m128 cvec = _mm_setzero_ps();
            __m128 bvec = _mm_load_ps(b[i*4]);
            __m128 avec = _mm_load1_ps(a[i]);//?
            
            cvec = _mm_add_ps(cvec,_mm_mul_ps(bvec,avec));
            cvec = _mm_add_ps(cvec, _mm_loadu_ps(c2[i*n+j*4]));
            _mm_storeu_ps(c2[i*n+j*4],cvec);
            
        }
    }*/




    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("simd: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("simd_matmul");
}

void loop_unroll_simd_matmul(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // c2 = a * b
    // TODO: implement me!
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("unroll+simd: %f\n", (float) (end.tv_sec - start.tv_sec) + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0f);
    check_correctness("loop_unroll_simd_matmul");
}


int main(void) {
    init();

    //naive_matmul();
    simd_matmul();
    loop_unroll_matmul();
    loop_unroll_simd_matmul();

    return 0;
}

