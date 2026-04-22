# Parallel 2D FFT using OpenMP

This project explores the parallelization of a 2D Split-Radix Fast Fourier Transform (FFT) using OpenMP. The base implementation is derived from Ooura’s FFT library, and this work focuses on introducing parallel execution and improving performance.

## Overview

A 2D FFT is computed by applying 1D FFT operations across the rows and columns of a matrix. Since each row can be processed independently, the row-wise stage presents a natural opportunity for parallelization.

## Current Status

This project is actively being developed. At the current stage:

- The original serial implementation has been studied and verified
- A parallel version has been introduced (`fftsg2d_v1.c`)
- OpenMP directives have been applied to independent loops
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

This approach avoids race conditions and allows concurrent execution across multiple rows.

Project Structure
src/            Core FFT implementation
benchmarks/     Performance testing programs
sample/         Original test harness from Ooura
Build

Compile the project using GCC with OpenMP support:

gcc -O3 -fopenmp src/fftsg.c src/fftsg2d_v1.c -o fft2d -lm
Run
./fft2d
Correctness

The parallel implementation has been tested against the serial version to ensure correctness. Observed numerical differences are minimal and consistent with floating-point precision limits.

Limitations
Parallelization is currently limited to selected portions of the code
Full performance benchmarking and scalability analysis are in progress
Additional optimization opportunities (e.g., column-wise parallelization) have not yet been implemented
Future Work
Extend parallelization to column-wise transforms
Explore OpenMP scheduling strategies and loop collapsing
Perform detailed performance benchmarking and speedup analysis
Evaluate scalability on multi-core systems
Acknowledgment

The original FFT routines are based on Ooura’s FFT library. Modifications in this project focus on parallel execution and performance evaluation.
