#include <capstone/capstone.h>
#include <inttypes.h>
#include <stdio.h>

#define CODE "\x55\x48\x8b\x05\xb8\x13\x00\x00"

static csh handle;

int init() {
	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
		return -1;
	return 0;
}

void fini() { cs_close(&handle); }

cs_insn *disassemble(const char *code, size_t *count) {
	cs_insn *insn;
	*count = cs_disasm(handle, (const uint8_t *)CODE, sizeof(CODE) - 1, 0x1000,
					   0, &insn);
	if (*count > 0)
		return insn;
	return NULL;
}
