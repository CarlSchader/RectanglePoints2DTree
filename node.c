#if defined(__MSVS__)
#include "pch.h"
#endif

#include "node.h"
#include "point_search.h"
#include <stdlib.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

void node_insert(struct Node* root, struct Point point) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->point = point;
    new_node->left = NULL;
    new_node->right = NULL;

    struct Node* current = root;
    int dim = 0;
    while (1) {
        if ((dim == 0 && point.x < current->point.x) || (dim == 1 && point.y < current->point.y)) {
            if (current->left == NULL) {
                current->left = new_node;
                return;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->right == NULL) {
                current->right = new_node;
                return;
            }
            else {
                current = current->right;
            }
        }
        dim = (dim + 1) % 2;
    }

}

void node_destroy(struct Node* root) {
    if (root != NULL) {
        node_destroy(root->left);
        node_destroy(root->right);
        free(root);
    }
}

void node_rect_search(struct Node* root, struct Point* points_buffer, struct Rect rect, int dim, int* found_count) {
    if (root != NULL) {
        if (dim == 0) {
            if (root->point.x < rect.lx) {
                node_rect_search(root->right, points_buffer, rect, (dim + 1) % 2, found_count);
            }
            else if (root->point.x > rect.hx) {
                node_rect_search(root->left, points_buffer, rect, (dim + 1) % 2, found_count);
            }
            else {
                if (root->point.y >= rect.ly && root->point.y <= rect.hy) {
                    points_buffer[*found_count] = root->point;
                    (*found_count)++;
                }
                node_rect_search(root->right, points_buffer, rect, (dim + 1) % 2, found_count);
                node_rect_search(root->left, points_buffer, rect, (dim + 1) % 2, found_count);
            }
        }
        else {
            if (root->point.y < rect.ly) {
                node_rect_search(root->right, points_buffer, rect, (dim + 1) % 2, found_count);
            }
            else if (root->point.y > rect.hy) {
                node_rect_search(root->left, points_buffer, rect, (dim + 1) % 2, found_count);
            }
            else {
                if (root->point.x >= rect.lx && root->point.x <= rect.hx) {
                    points_buffer[*found_count] = root->point;
                    (*found_count)++;
                }
                node_rect_search(root->right, points_buffer, rect, (dim + 1) % 2, found_count);
                node_rect_search(root->left, points_buffer, rect, (dim + 1) % 2, found_count);
            }
        }
    }
}

void print_tree(struct Node* root) {
    if (root != NULL) {
        print_point(root->point);
        print_tree(root->left);
        print_tree(root->right);
    }
}