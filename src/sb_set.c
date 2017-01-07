#include "sb_set.h"
#include <stdio.h>
#include <stdlib.h>

#define BITMASK(b) (1 << ((b) % 8))
#define BITSLOT(b) ((b) / 8)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + 8 - 1) / 8)

sb_set *sb_set_allocate(size_t size) {
	sb_set *set = calloc(1, sizeof(sb_set));
	if (!set)
		return NULL;
	set->bitset_len = size;
	set->bitset = calloc(1, BITNSLOTS(size));
	if (!set->bitset)
		return NULL;
	return set;
}

static inline sb_node find_hash_entry(sb_node_list hashmap[], uint16_t key) {
	sb_node_list *collision_list = &hashmap[key % LN_SIZE];
	for (sb_node node = collision_list->node; node;
		 node = collision_list->node) {
		if (*node == key)
			return node;
		if (!collision_list->next)
			return NULL;
		collision_list = collision_list->next;
	}
	return NULL;
}

int sb_set_test(sb_set *set, uintptr_t key) {
	sb_node node;
	sb_node_list *hashmap = set->l1_bucket_lists;
	for (int i = 48; i >= 16;
		 i -= 16, hashmap = ((sb_inode *)node)->bucket_lists) {
		node = find_hash_entry(hashmap, (uint16_t)(key >> i));
		if (!node)
			return 0;
	}
	return BITTEST(((sb_leaf *)node)->bitset, key & 0xffff);
}

static inline sb_node make_or_get(sb_node_list hashmap[], uint16_t key,
								  size_t alloc_size) {
	sb_node_list *collision_list = &hashmap[key % LN_SIZE];
	sb_node node = collision_list->node;
	for (; node; node = collision_list->node) {
		if (*node == key)
			return node;
		if (!collision_list->next) {
			sb_node_list *next_node = calloc(1, sizeof(sb_node_list));
			if (!next_node)
				return NULL;
			collision_list->next = next_node;
			collision_list = next_node;
			break;
		}
		collision_list = collision_list->next;
	}
	collision_list->node = calloc(1, alloc_size);
	if (!collision_list->node)
		return NULL;
	*collision_list->node = key;

	return collision_list->node;
}

// return 0 for failure
int sb_set_set(sb_set *set, uintptr_t key) {
	sb_node node;
	sb_node_list *hashmap = set->l1_bucket_lists;
	for (int i = 48; i >= 16;
		 i -= 16, hashmap = ((sb_inode *)node)->bucket_lists) {
		node = make_or_get(hashmap, (uint16_t)(key >> i),
						   i != 16 ? sizeof(sb_inode) : sizeof(sb_leaf));
		if (!node)
			return 0;
	}
	uint8_t **bitset = &((sb_leaf *)node)->bitset;
	if (!*bitset) {
		*bitset = set->bitset + (LEAF_SIZE * set->used_blocks++);
	}
	BITSET(*bitset, key & 0xffff);
	return 1;
}
