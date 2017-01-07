#include "sb_set.h"
#include <stdio.h>

int main() {
	// asm("call *posvm_entry_ptr");
	sb_set *set = sb_set_allocate(800000);
	if (!set) {
		perror("Failed to allocate set");
		exit(-1);
	}
	if (!sb_set_set(set, 0)) {
		perror("Failed to set value");
		exit(-1);
	}
	if (!sb_set_set(set, 1)) {
		perror("Failed to set value");
		exit(-1);
	}
	if (!sb_set_set(set, 65536)) {
		perror("Failed to set value");
		exit(-1);
	}
	if (!sb_set_set(set, 65537)) {
		perror("Failed to set value");
		exit(-1);
	}
	if (!sb_set_test(set, 0)) {
		printf("Failed to get %d\n", 0);
	}
	if (!sb_set_test(set, 1)) {
		printf("Failed to get %d\n", 0);
	}
	if (!sb_set_test(set, 65536)) {
		printf("Failed to get %d\n", 0);
	}
	if (!sb_set_test(set, 65537)) {
		printf("Failed to get %d\n", 0);
	}
	printf("Blocks used %d\n", set->used_blocks);
	return 0;
}
