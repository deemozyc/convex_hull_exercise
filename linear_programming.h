#ifndef LINEAR_H
#define LINEAR_H

#include "helper.h"

using namespace std;

long double one_d_linear(const vector<long double> &a, const vector<long double> &b, long double c, int *flag, int *index);

vector<point> find_bridge(vector<point> &p, long double pivot, int *flag);

#endif