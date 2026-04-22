#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Signature from your fftsg2d.c:
void cdft2d(int n1, int n2, int isgn, double **a, double *t, int *ip, double *w);

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main(int argc, char **argv) {
    int N = (argc >= 2) ? atoi(argv[1]) : 1024;   // N x N complex grid
    if (N <= 0) {
        fprintf(stderr, "Usage: %s [N]\n", argv[0]);
        return 1;
    }

    // Each row has 2*N doubles: [re0, im0, re1, im1, ...]
    int n1 = N;
    int n2 = 2 * N;

    // Allocate a[n1][n2] contiguously + row pointers
    size_t row_len = (size_t)n2;
    double *data = (double*)malloc((size_t)n1 * row_len * sizeof(double));
    double **a = (double**)malloc((size_t)n1 * sizeof(double*));
    if (!data || !a) {
        fprintf(stderr, "Allocation failed for a\n");
        return 1;
    }
    for (int i = 0; i < n1; i++) a[i] = data + (size_t)i * row_len;

    // Initialize input
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            a[i][j] = (double)((i + 1) * (j + 1)) * 1e-6;
        }
    }

    // Work arrays (generous sizing to start)
    int *ip = (int*)calloc((size_t)(2 * N + 1024), sizeof(int));
    double *w = (double*)calloc((size_t)(2 * N + 1024), sizeof(double));
    double *t = (double*)calloc((size_t)(2 * N + 1024), sizeof(double)); // temp buffer required
    if (!ip || !w || !t) {
        fprintf(stderr, "Allocation failed for work arrays\n");
        return 1;
    }
    ip[0] = 0; // required init for Ooura routines

    // Warm-up
    cdft2d(n1, n2, 1, a, t, ip, w);

    // Timed run
    double t0 = now_sec();
    cdft2d(n1, n2, 1, a, t, ip, w);
    double t1 = now_sec();

    printf("N=%d  serial cdft2d time = %.6f s\n", N, (t1 - t0));

    free(t);
    free(w);
    free(ip);
    free(a);
    free(data);
    return 0;
}
