#ifndef _SB_SET_
#define _SB_SET_
#include <stdint.h>
#include <stdlib.h>

#define LN_SIZE 256
#define LEAF_SIZE (1 << 16) / 8

typedef uint16_t *sb_node;

typedef struct sb_node_list {
	sb_node node;
	struct sb_node_list *next;
} sb_node_list;

typedef struct {
	uint16_t key;
	uint8_t *bitset;
} sb_leaf;

typedef struct {
	uint16_t key;
	sb_node_list bucket_lists[LN_SIZE];
} sb_inode;

typedef struct {
	size_t bitset_len;
	uint8_t *bitset;
	uint32_t used_blocks;
	sb_node_list l1_bucket_lists[LN_SIZE];
} sb_set;

sb_set *sb_set_allocate(size_t size);
int sb_set_test(sb_set *set, uintptr_t key);
int sb_set_set(sb_set *set, uintptr_t key);

#endif
