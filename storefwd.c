//  -xCORE-AVX512 stdfwd.c -o  stdfwd.o
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define ITERATIONS 100000000
#define RUNS 5

static inline uint64_t rdtsc() {
    uint64_t a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (d << 32) | a;
}

void benchmark_int() {
    volatile int data __attribute__((aligned(64))) = 0;
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            data = i;
            int temp = data;
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            data = i;
            int temp = data;
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (int): Average %lu cycles\n", total_cycles / RUNS);
}

void benchmark_long() {
    volatile long data __attribute__((aligned(64))) = 0;
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            data = i;
            long temp = data;
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            data = i;
            long temp = data;
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (long): Average %lu cycles\n", total_cycles / RUNS);
}

void benchmark_float() {
    volatile float data __attribute__((aligned(64))) = 0.0f;
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            data = (float)i;
            float temp = data;
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            data = (float)i;
            float temp = data;
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (float): Average %lu cycles\n", total_cycles / RUNS);
}

void benchmark_double() {
    volatile double data[2] __attribute__((aligned(64))) = {0.0, 0.0};
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            data[0] = (double)i;
            float temp = (float)data[0];
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            data[0] = (double)i;
            float temp = (float)data[0];
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (Wide Store, Narrow Load - double to float): Average %lu cycles\n", total_cycles / RUNS);
}

void benchmark_double_1() {
    volatile double data[2] __attribute__((aligned(64))) = {0.0, 0.0};
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            data[0] = (double)i;
            float temp = (float)data[0];
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            data[0] = (double)i;
            double temp = data[0];
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (Same Store, Same Load - double ): Average %lu cycles\n", total_cycles / RUNS);
}

int main() {
    benchmark_int();
    benchmark_long();
    benchmark_float();
    benchmark_double();
    benchmark_double_1();

    return 0;
}
