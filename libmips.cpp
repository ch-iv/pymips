#include <print>

int* t0 = new int(0);
int* t1 = new int(0);
int* t2 = new int(0);

void _instr_add(int *dest, int *src1, int *src2) {
    *dest = *src1 + *src2;
}

void _instr_li(int *dest, int value) {
    *dest = value;
}

void _mips_dump_registers() {
    std::println("t0: {}", *t0);
    std::println("t1: {}", *t1);
    std::println("t2: {}", *t2);
}