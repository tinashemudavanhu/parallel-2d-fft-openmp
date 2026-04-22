/* bench_cdft2d.c
   Serial timing driver for Ooura fftsg2d.c (2D complex DFT only)

   Usage (interactive):
     ./bench_cdft2d_serial
     then enter n1 and n2 when prompted.

   Note for complex N×N grid:
     n1 = N
     n2 = 2*N   (because data is stored as [Re,Im,Re,Im,...] per row)
*/

#include <math.h>
#include <stdio.h>
#include <time.h>
#include "alloc.h"

#define MAX(x,y) ((x) > (y) ? (x) : (y))

/* random number generator, 0 <= RND < 1 */
#define RND(p) ((*(p) = (*(p) * 7141 + 54773) % 259200) * (1.0 / 259200))

static double now_sec(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
}

static void putdata2d(int n1, int n2, double **a)
{
    int j1, j2, seed = 0;
    for (j1 = 0; j1 <= n1 - 1; j1++) {
        for (j2 = 0; j2 <= n2 - 1; j2++) {
            a[j1][j2] = RND(&seed);
        }
    }
}

static double errorcheck2d(int n1, int n2, double scale, double **a)
{
    int j1, j2, seed = 0;
    double err = 0, e;

    for (j1 = 0; j1 <= n1 - 1; j1++) {
        for (j2 = 0; j2 <= n2 - 1; j2++) {
            e = RND(&seed) - a[j1][j2] * scale;
            err = MAX(err, fabs(e));
        }
    }
    return err;
}

int main(void)
{
    /* Ooura 2D complex DFT (from fftsg2d.c) */
    void cdft2d(int, int, int, double **, double *, int *, double *);

    int *ip, n1, n2, n;
    double **a, *w, err;

    printf("data length n1=? (n1 = power of 2)\n");
    if (scanf("%d", &n1) != 1) {
        fprintf(stderr, "Failed to read n1\n");
        return 1;
    }

    printf("data length n2=? (n2 = power of 2)\n");
    if (scanf("%d", &n2) != 1) {
        fprintf(stderr, "Failed to read n2\n");
        return 1;
    }

    a = alloc_2d_double(n1, n2);

    /* Workspace sizing exactly like the official test program */
    n = MAX(n1, n2 / 2);
    ip = alloc_1d_int(2 + (int) sqrt(n + 0.5));
    n = MAX(n1, n2) * 3 / 2;
    w = alloc_1d_double(n);
    ip[0] = 0;

    /* Initialize input */
    putdata2d(n1, n2, a);

    /* Warm-up (not timed) */
    cdft2d(n1, n2, 1, a, NULL, ip, w);
    cdft2d(n1, n2, -1, a, NULL, ip, w);

    /* Re-init so correctness check matches */
    putdata2d(n1, n2, a);

    /* Timed forward + inverse */
    double t0 = now_sec();
    cdft2d(n1, n2, 1, a, NULL, ip, w);
    cdft2d(n1, n2, -1, a, NULL, ip, w);
    double t1 = now_sec();

    /* Correctness check (same as official test) */
    err = errorcheck2d(n1, n2, 2.0 / n1 / n2, a);
    printf("cdft2d err= %g\n", err);
    printf("cdft2d time (forward+inverse) = %.6f s\n", (t1 - t0));

    free_1d_double(w);
    free_1d_int(ip);
    free_2d_double(a);

    return 0;
}
