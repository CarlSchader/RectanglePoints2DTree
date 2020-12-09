#ifndef POINT_ALG_H
#define POINT_ALG_H

#include "point_search.h"

int partition(struct Point* points, int left, int right);

void quicksort(struct Point* points, int left, int right);

void k_snallest(struct Point* points, int k, int left, int right);

#endif