#ifndef NODE_H
#define NODE_H

#include "point_search.h"
#include <stdint.h>

#pragma(push, 1)

struct Node {
	struct Point point;
	struct Node* left;
	struct Node* right;
};

#pragma(pop)

void node_insert(struct Node* root, struct Point point);

void node_destroy(struct Node* root);

void node_rect_search(struct Node* root, struct Point* points_buffer, struct Rect rect, int dim, int* found_count);

void print_tree(struct Node* root);

#endif