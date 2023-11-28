#ifndef HELPER_H
#define HELPER_H

#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

// the inf should be larger than any number in convex computation.
// there are test case that y=x^2, and data size is 4e6
// so the inf should be at least bigger than 1.6e13
const long double inf = 1e18;
const long double eps = 1e-9;
const long double pi = acos(-1);

struct point
{
    long double x, y;
    point() {}
    point(long double x, long double y) : x(x), y(y) {}

    bool operator==(const point &other) const;
    bool operator!=(const point &other) const;
    bool operator<(const point &other) const;
};

struct point_hash // for unordered_map<point, something, point_hash>
{
    size_t operator()(const point &p) const;
};

int cmp(const point &a, const point &b);

int cmp_2(const point &a, const point &b);

long double turn_test(const point &p1, const point &p2, const point &p3);

long double dis(const point &a, const point &b);

long double clockwise_angle(const point &a, const point &b, const point &c);

vector<point> top_sort(const vector<pair<point, point>> &line_vec);

void flip_points(vector<point>::iterator begin, vector<point>::iterator end);

#endif