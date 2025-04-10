//

#include <stdio.h>
#include <stdint.h>
#include <immintrin.h> 

#define ITERATIONS 100000000
#define RUNS 5

static inline uint64_t rdtsc() {
    uint64_t a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (d << 32) | a;
}

void benchmark_xmm() {
    float mem[4] __attribute__((aligned(16))) = {0};
    __m128 data = _mm_setzero_ps();
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            _mm_store_ps(mem, data);
            __m128 temp = _mm_load_ps(mem);
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            _mm_store_ps(mem, _mm_set1_ps((float)i));
            __m128 temp = _mm_load_ps(mem);
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (XMM): Average %lu cycles\n", total_cycles / RUNS);
}

void benchmark_ymm() {
    float mem[8] __attribute__((aligned(32))) = {0};
    __m256 data = _mm256_setzero_ps();
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            _mm256_store_ps(mem, data);
            __m256 temp = _mm256_load_ps(mem);
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            _mm256_store_ps(mem, _mm256_set1_ps((float)i));
            __m256 temp = _mm256_load_ps(mem);
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (YMM): Average %lu cycles\n", total_cycles / RUNS);
}

#ifdef __AVX512F__
void benchmark_zmm() {
    float mem[16] __attribute__((aligned(64))) = {0};
    __m512 data = _mm512_setzero_ps();
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            _mm512_store_ps(mem, data);
            __m512 temp = _mm512_load_ps(mem);
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            _mm512_store_ps(mem, _mm512_set1_ps((float)i));
            __m512 temp = _mm512_load_ps(mem);
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (ZMM): Average %lu cycles\n", total_cycles / RUNS);
}
#endif

void benchmark_large_store_narrow_load() {
    float mem[8] __attribute__((aligned(32))) = {0};
    __m256 data = _mm256_set1_ps(1.0f);
    uint64_t start, end, total_cycles = 0;
    int i, run;

    for (run = 0; run < RUNS; run++) {
        for (i = 0; i < 1000; i++) {
            _mm256_store_ps(mem, data);
            __m128 temp = _mm_load_ps(mem);
        }

        start = rdtsc();
        for (i = 0; i < ITERATIONS; i++) {
            _mm256_store_ps(mem, _mm256_set1_ps((float)i));
            __m128 temp = _mm_load_ps(mem);
            asm volatile("" ::: "memory");
        }
        end = rdtsc();

        total_cycles += (end - start);
    }

    printf("Store forwarding benchmark (Large Store, Narrow Load): Average %lu cycles\n", total_cycles / RUNS);
}

int main() {
    benchmark_xmm();
    benchmark_ymm();
#ifdef __AVX512F__
    benchmark_zmm();
#else
    printf("AVX-512 not supported on this system.\n");
#endif
    benchmark_large_store_narrow_load();

    return 0;
}
