#include "point_alg.h"
#if defined(__MSVS__)
#include "pch.h"
#endif

#include "point_search.h"
#include <stdlib.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

int partition(struct Point* points, int left, int right) {
    int32_t pivot_rank = points[right].rank;
    int i = left - 1;
    struct Point buffer_point;
    for (int j = left; j <= right; j++) {
        if (points[j].rank < pivot_rank) {
            i++;
            buffer_point = points[i];
            points[i] = points[j];
            points[j] = buffer_point;
        }
    }
    i++;
    buffer_point = points[i];
    points[i] = points[right];
    points[right] = buffer_point;
    return i;
}

void quicksort(struct Point* points, int left, int right) {
    if (left < right) {
        int partition_index = partition(points, left, right);
        quicksort(points, left, partition_index - 1);
        quicksort(points, partition_index + 1, right);
    }
}

void k_snallest(struct Point* points, int k, int left, int right) {
    while (k > 0 && k < right - left + 1) {
        int partition_index = partition(points, left, right);
        if (partition_index == k || partition_index == k + 1) {
            return;
        }
        else if (partition_index < k) {
            k = k - (partition_index + 1 - left);
            left = partition_index + 1;
        }
        else {
            right = partition_index - 1;
        }
    }
}