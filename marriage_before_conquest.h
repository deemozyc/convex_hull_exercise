#ifndef MBC_H
#define MBC_H

#include "linear_programming.h"

using namespace std;

class Mbc
{
public:
    vector<point> convex_line;
    vector<point> points;

    Mbc(vector<point> &p);

    void mbc_upper(vector<point> &p);

    vector<point> mbc_full();
};

#endif