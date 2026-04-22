# Parallel 2D FFT using OpenMP

This project explores the parallelization of a 2D Split-Radix Fast Fourier Transform (FFT) using OpenMP. The base implementation is derived from Ooura’s FFT library, and this work focuses on analyzing and introducing parallel execution to improve performance.

## Overview

A 2D FFT is computed by applying 1D FFT operations across rows and columns of a matrix. Since each row can be processed independently, the row-wise stage presents a natural opportunity for parallelization.

## Current Status

This project is actively being developed. At the current stage:

- The original serial implementation has been studied and verified
- A parallel version has been introduced (`fftsg2d_v1.c`)
- Initial OpenMP directives have been applied to independent loops
- Basic testing has been performed to ensure correctness

Further optimization and performance evaluation are ongoing.

## My Contribution

- Analyzed the structure of Ooura’s 2D FFT implementation
- Identified independent computation regions suitable for parallel execution
- Introduced OpenMP-based parallelization to the row-wise transform
- Organized the project structure for clarity and reproducibility

## Parallelization Approach

The primary parallelization target is the row-wise FFT loop, where each iteration operates on independent data:

```c
#pragma omp parallel for
for (i = 0; i < n1; i++) {
    // Apply FFT to each row independently
}
