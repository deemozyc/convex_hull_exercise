#include "marriage_before_conquest.h"

using namespace std;

Mbc::Mbc(vector<point> &p)
{
    points = p;
    convex_line = {};
}

void Mbc::mbc_upper(vector<point> &p)
// marriage before conquest algorithm to find upper hull
{
    int n = p.size();
    if (n == 0)
        return;
    if (n == 1)
    {
        convex_line.push_back(p[0]);
        return;
    }
    if (n == 2)
    {
        convex_line.push_back(min(p[0], p[1]));
        convex_line.push_back(max(p[0], p[1]));
        return;
    }

    // test cases contain points with integer coordinates
    // we don't want any point to lie on the pivot, that's why adding 0.1
    long double mid_x = (p[0].x + p[1].x) / 2 + 0.1;
    
    int flag;
    vector<point> bridge = find_bridge(p, mid_x, &flag);

    if (flag != 0)
    {
        // debug
        printf("flag:%d, mid_x: %Lf\n", flag, mid_x);
        for (auto it : p)
        {
            printf("points: %Lf, %Lf\n", it.x, it.y);
        }
    }
    vector<point> pl, pr;
    if(bridge.size() == 1) // bridge is a vertical line
    {
        for (auto &it : p)
        {
            if (it.x < bridge[0].x)
            {
                pl.push_back(it);
            }
        }
        // important! put current pivot at the end so it is not selected as a pivot again in the next recurrence execution
        pl.push_back(bridge[0]); 
    }
    else if(bridge.size() == 2)
    {
        if(bridge[0].x > bridge[1].x)
        {
            swap(bridge[0], bridge[1]);
        }

        for (auto &it : p)
        {
            if (it.x > bridge[1].x)
            {
                pr.push_back(it);
            }
            else if (it.x < bridge[0].x)
            {
                pl.push_back(it);
            }
        }
        pl.push_back(bridge[0]);
        pr.push_back(bridge[1]);
    }
    else if(bridge.size() == 0)
    {
        // debug
        printf("Bridge not found");
    }
    mbc_upper(pl);
    mbc_upper(pr);

    return;
}

vector<point> Mbc::mbc_full()
{

    // compute full convex of full_points.
    mbc_upper(points);

    flip_points(points.begin(), points.end());

    int bottom_hull_start = convex_line.size();
    mbc_upper(points);

    flip_points(points.begin(), points.end()); // turn to original full_p
    // turn points on the lower hull to original space
    flip_points(convex_line.begin() + bottom_hull_start, convex_line.end());

    // and if there are vertical line in the right side of convec hull,
    // convex_line may not include the last line somehow.
    // so, add it if it is missing.
    if (convex_line[0] != convex_line[convex_line.size() - 1])
    {
        convex_line.push_back(convex_line[0]);
    }
    return convex_line;
}
