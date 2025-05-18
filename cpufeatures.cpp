// CPU Feature test that works on windows.
#include <iostream>
#include <intrin.h>

void print_cpu_features() {
    int cpuInfo[4] = {0};

    // Get the highest valid function ID
    __cpuid(cpuInfo, 0);
    int nIds = cpuInfo[0];

    // Get feature bits from function 1
    __cpuid(cpuInfo, 1);
    bool sse3     = (cpuInfo[2] & (1 << 0)) != 0;
    bool pclmul   = (cpuInfo[2] & (1 << 1)) != 0;
    bool ssse3    = (cpuInfo[2] & (1 << 9)) != 0;
    bool fma      = (cpuInfo[2] & (1 << 12)) != 0;
    bool sse41    = (cpuInfo[2] & (1 << 19)) != 0;
    bool sse42    = (cpuInfo[2] & (1 << 20)) != 0;
    bool movbe    = (cpuInfo[2] & (1 << 22)) != 0;
    bool popcnt   = (cpuInfo[2] & (1 << 23)) != 0;
    bool aes      = (cpuInfo[2] & (1 << 25)) != 0;
    bool xsave    = (cpuInfo[2] & (1 << 26)) != 0;
    bool osxsave  = (cpuInfo[2] & (1 << 27)) != 0;
    bool avx      = (cpuInfo[2] & (1 << 28)) != 0;
    bool f16c     = (cpuInfo[2] & (1 << 29)) != 0;
    bool rdrand   = (cpuInfo[2] & (1 << 30)) != 0;
    bool sse      = (cpuInfo[3] & (1 << 25)) != 0;
    bool sse2     = (cpuInfo[3] & (1 << 26)) != 0;

    // Get feature bits from function 7, sub-leaf 0
    if (nIds >= 7) {
        __cpuidex(cpuInfo, 7, 0);
        bool avx2      = (cpuInfo[1] & (1 << 5)) != 0;
        bool bmi1      = (cpuInfo[1] & (1 << 3)) != 0;
        bool bmi2      = (cpuInfo[1] & (1 << 8)) != 0;
        bool adx       = (cpuInfo[1] & (1 << 19)) != 0;
        bool sha       = (cpuInfo[1] & (1 << 29)) != 0;
        bool avx512f   = (cpuInfo[1] & (1 << 16)) != 0;
        bool avx512dq  = (cpuInfo[1] & (1 << 17)) != 0;
        bool avx512ifma= (cpuInfo[1] & (1 << 21)) != 0;
        bool avx512pf  = (cpuInfo[1] & (1 << 26)) != 0;
        bool avx512er  = (cpuInfo[1] & (1 << 27)) != 0;
        bool avx512cd  = (cpuInfo[1] & (1 << 28)) != 0;
        bool avx512bw  = (cpuInfo[1] & (1 << 30)) != 0;
        bool avx512vl  = (cpuInfo[1] & (1 << 31)) != 0;

        std::cout << "AVX2:      " << avx2 << std::endl;
        std::cout << "BMI1:      " << bmi1 << std::endl;
        std::cout << "BMI2:      " << bmi2 << std::endl;
        std::cout << "ADX:       " << adx << std::endl;
        std::cout << "SHA:       " << sha << std::endl;
        std::cout << "AVX-512F:  " << avx512f << std::endl;
        std::cout << "AVX-512DQ: " << avx512dq << std::endl;
        std::cout << "AVX-512IFMA:" << avx512ifma << std::endl;
        std::cout << "AVX-512PF: " << avx512pf << std::endl;
        std::cout << "AVX-512ER: " << avx512er << std::endl;
        std::cout << "AVX-512CD: " << avx512cd << std::endl;
        std::cout << "AVX-512BW: " << avx512bw << std::endl;
        std::cout << "AVX-512VL: " << avx512vl << std::endl;
    }

    std::cout << "SSE:       " << sse << std::endl;
    std::cout << "SSE2:      " << sse2 << std::endl;
    std::cout << "SSE3:      " << sse3 << std::endl;
    std::cout << "SSSE3:     " << ssse3 << std::endl;
    std::cout << "SSE4.1:    " << sse41 << std::endl;
    std::cout << "SSE4.2:    " << sse42 << std::endl;
    std::cout << "FMA:       " << fma << std::endl;
    std::cout << "MOVBE:     " << movbe << std::endl;
    std::cout << "POPCNT:    " << popcnt << std::endl;
    std::cout << "AES:       " << aes << std::endl;
    std::cout << "XSAVE:     " << xsave << std::endl;
    std::cout << "OSXSAVE:   " << osxsave << std::endl;
    std::cout << "AVX:       " << avx << std::endl;
    std::cout << "F16C:      " << f16c << std::endl;
    std::cout << "RDRAND:    " << rdrand << std::endl;
    std::cout << "PCLMULQDQ: " << pclmul << std::endl;
}

int main() {
    print_cpu_features();
    return 0;
}
