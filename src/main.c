#include "sb_set.h"
#include <stdio.h>

int main() {
	// asm("call *posvm_entry_ptr");
	sb_set *set = sb_set_allocate(800000);
	if (!set) {
		perror("Failed to allocate set");
		exit(-1);
	}
	if (!sb_set_set(set, 10)) {
		perror("Failed to set value");
		exit(-1);
	}
	if (!sb_set_set(set, 11)) {
		perror("Failed to set value");
		exit(-1);
	}
	return 0;
}
