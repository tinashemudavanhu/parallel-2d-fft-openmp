# Parallel 2D FFT using OpenMP

This project explores the parallelization of a 2D Split-Radix Fast Fourier Transform (FFT) using OpenMP. The base implementation is derived from Ooura’s FFT library. The focus of this work is on introducing parallel execution, validating correctness, and evaluating performance on a multi-core HPC system.

## Overview

A 2D FFT is computed by applying 1D FFT operations across the rows and columns of a matrix. The original implementation follows Ooura’s structure, where row-wise transforms are applied first, followed by column-direction processing.

The OpenMP implementation parallelizes independent computation regions within this workflow.

## Current Status

At this stage:

- The serial implementation has been verified
- The OpenMP version (fftsg2d_v1.c) has been implemented
- The code has been executed on the DARWIN HPC cluster
- Performance has been evaluated across multiple thread counts
- Numerical correctness has been validated (error ≈ 1e-15)

## My Contribution

- Analyzed Ooura’s 2D FFT implementation
- Identified independent computation regions
- Implemented OpenMP parallelization
- Designed and executed performance experiments on DARWIN
- Compared serial and parallel performance

## Parallelization Approach

Parallelization is applied to both stages of the 2D FFT:

Row-wise transform:
```bash
#pragma omp parallel for
for (i = 0; i < n1; i++) {
    // Apply FFT across each row
}
```
Column-direction processing is handled inside cdft2d_sub and is also parallelized.

## Project Structure
```
parallel-2d-fft-openmp/
├── src/
├── sample/sample2d/
├── results/
├── readme2d.txt
└── README.md
```

## Build

From sample/sample2d:

```bash
gcc -O2 -Wall -fopenmp bench_cdft2d.c ../../src/fftsg2d_v1.c ../../src/fftsg.c ../../src/alloc.c -lm -o bench_cdft2d_omp
```
## Run

```printf "16384\n32768\n" | ./bench_cdft2d_omp```

## Execution Environment

DARWIN HPC:

- Node: r1n32
- CPU: AMD EPYC 7502
- Cores: 64
- Memory: ~488 GB


## Performance Results

### Runtime (seconds)
```markdown

| Threads | 16384 × 32768 | 32768 × 65536 |
|--------|--------------|--------------|
| 8      | 2.79         | 13.11        |
| 16     | 2.31         | 7.96         |
| 32     | 1.67         | 6.38         |
| 64     | 1.22         | 6.05         |

```
## Observations

- Strong scaling up to 32 threads
- Diminishing returns after 32 threads
- Memory/data movement impacts large sizes

## Correctness

cdft2d err ≈ 1e-15

## Limitations

- Partial parallelization
- Memory-bound behavior at scale

## Future Work

- Improve memory access patterns
- Explore OpenMP scheduling
- Add fine-grained timing

## Acknowledgment

Based on Ooura FFT library.

