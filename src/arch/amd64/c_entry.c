#include "asm.h"
#include <stdio.h>

void _c_posvm_entry(pt_regs *regs) { printf("Got Regs %p\n", regs); }
