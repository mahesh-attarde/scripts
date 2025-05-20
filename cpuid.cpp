// compile
// g++ cpuid.cpp
// RUN: sde -nvl -- ./a.out 
// RUN: ./a.out
#include <stdio.h>

void cpuid(int code, unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "0"(code));
}

int main() {
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, &eax, &ebx, &ecx, &edx);

    unsigned int family = ((eax >> 8) & 0xF) + ((eax >> 20) & 0xFF);
    unsigned int model = ((eax >> 4) & 0xF) + ((eax >> 16) & 0xF);
    printf("This CPU processor. hex family %x model %x\n", family, model);

    return 0;
}
