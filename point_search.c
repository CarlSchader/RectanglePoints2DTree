#if defined(__MSVS__)
#include "pch.h"
#endif

#include "point_search.h"
#include "node.h"
#include "point_alg.h"
#include <stdlib.h>
#include <stdio.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

struct  SearchContext* __stdcall create(const struct Point* points_begin, const struct Point* points_end) {
    struct SearchContext* sc = (struct SearchContext*)malloc(sizeof(struct SearchContext));
    if (points_begin == NULL) {
        return sc;
    }
    
    sc->root = (struct Node*)malloc(sizeof(struct Node));
    int size = 0;
    
    sc->root->point = *points_begin;
    points_begin++;
    size++;
    while (points_begin != points_end) {
        node_insert(sc->root, *points_begin);
        points_begin++;
        size++;
    }
    sc->size = size;

    return sc;
}

int32_t __stdcall search(struct SearchContext* sc, const struct Rect rect, const int32_t count, struct Point* out_points) {
    if (count == 0 || out_points == NULL) {
        return 0;
    }

    struct Point* points_buffer = (struct Point*)malloc(sc->size * sizeof(struct Point));
    int found_count = 0;
    node_rect_search(sc->root, points_buffer, rect, 0, &found_count);
    
    if (found_count < count) {
        for (int i = 0; i < found_count; i++) {
            out_points[i] = points_buffer[i];
        }
        free(points_buffer);
        quicksort(out_points, 0, found_count - 1);
        return found_count;
    }
    else {
        k_snallest(points_buffer, count, 0, found_count - 1);
        for (int i = 0; i < count; i++) {
            out_points[i] = points_buffer[i];
        }
        free(points_buffer);
        quicksort(out_points, 0, count - 1);
        return count;
    }
}

struct SearchContext* __stdcall destroy(struct SearchContext* sc) { // TODO: Figure out a reasonable way to handle error catching in C.
    node_destroy(sc->root);
    free(sc);
    return NULL;
}

//

void print_point(struct Point point) {
    printf("Point id: %d rank: %d x: %.2f y: %.2f\n", point.id, point.rank, point.x, point.y);
}

void print_points(struct Point* points, int number) {
    for (int i = 0; i < number; i++) {
        print_point(points[i]);
    }
}