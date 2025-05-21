// compile
// g++ cpuid.cpp
// RUN: sde -nvl -- ./a.out 
// RUN: ./a.out
#include <iostream>
#include <array>
#include <immintrin.h> // For __cpuid intrinsic on MSVC, or use <cpuid.h> for GCC/Clang

#if defined(_MSC_VER)
#include <intrin.h>
void cpuid(int info[4], int function_id) {
    __cpuid(info, function_id);
}
#else
#include <cpuid.h>
void cpuid(int info[4], int function_id) {
    __cpuid(function_id, info[0], info[1], info[2], info[3]);
}
#endif

int main() {
    int info[4] = {0};
    cpuid(info, 0);

    char vendor[13];
    ((int*)vendor)[0] = info[1]; // EBX
    ((int*)vendor)[1] = info[3]; // EDX
    ((int*)vendor)[2] = info[2]; // ECX
    vendor[12] = '\0';

    std::cout << "CPU Vendor: " << vendor << std::endl;

    cpuid(info, 1);
    std::cout << std::hex;
    std::cout << "Stepping: 0x" << (info[0] & 0xF) << std::endl;
    std::cout << "Model: 0x" << ((info[0] >> 4) & 0xF) << std::endl;
    std::cout << "Family: 0x" << ((info[0] >> 8) & 0xF) << std::endl;
    std::cout << "Processor Type: 0x" << ((info[0] >> 12) & 0x3) << std::endl;
    std::cout << "Extended Model: 0x" << ((info[0] >> 16) & 0xF) << std::endl;
    std::cout << "Extended Family: 0x" << ((info[0] >> 20) & 0xFF) << std::endl;

    // Family and Model Synthesized (Intel SDM Vol 2A, CPUID)
    int base_family = (info[0] >> 8) & 0xF;
    int ext_family = (info[0] >> 20) & 0xFF;
    int base_model = (info[0] >> 4) & 0xF;
    int ext_model = (info[0] >> 16) & 0xF;
    int family_synth = (base_family == 0xF) ? (base_family + ext_family) : base_family;
    int model_synth = (base_family == 0x6 || base_family == 0xF) ? (base_model + (ext_model << 4)) : base_model;

    std::cout << "Family (synth): 0x" << family_synth << std::endl;
    std::cout << "Model  (synth): 0x" << model_synth << std::endl;

    return 0;
}
