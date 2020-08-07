#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Full binary tree in which the leafs represent the clients open in the river tiling compositor for wayland
 */
struct bstree;
typedef struct bstree bstree;

/**
 * Creates and returns a new binary tree.
 * Must be deallocated by bstree_destroy.
 */
bstree *bstree_create(int width, int height, double masterWidthFactor);

/**
 * Destroys and deallocates all memory for the given tree 't'
 */
void bstree_destroy(bstree *t);

/**
 * Inserts a new client into tree 't'.
 * if master is true, client gets forcibly placed into the master side of the tree
 * (currently ignored)
 */
void bstree_insert(bstree *t, bool master);

/**
 * Prints the client dimensions of bstree 't' to the supplied output stream 'out'
 * Tree gets traversed in post order direction
 * each leaf represents a client 
 */
void bstree_print(const bstree *t, FILE *out);

#endif // _BSTREE_H_
