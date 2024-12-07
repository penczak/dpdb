// bplus.h
#ifndef BPLUS_H
#define BPLUS_H

#define NODE_N 64 // should be based on OS word size? is row cache? L0 cache?

typedef struct Node {
	int keys[NODE_N];
	struct Node* children[NODE_N - 1];
	bool isLeaf;
	int pagePtr; // only if isLeaf. line offest in file.
} Node;

#endif // !BPLUS_H
