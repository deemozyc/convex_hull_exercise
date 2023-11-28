#include "jarvis.h"

using namespace std;

Jarvis::Jarvis(int n)
{
    Jarvis::n = n;
    st.resize(n * 4);
    p.resize(n);
}

void Jarvis::do_jarvis()
{
    // sort(p.begin(), p.end(), cmp);
    point init_p = {inf, inf};
    for (auto &it : p)
    {
        if (it.x < init_p.x || (it.x == init_p.x && it.y < init_p.y))
            init_p = it;
    }
    top = 0;
    st[top++] = init_p;

    // upper hull
    while (1)
    {
        long double min_angle = inf;
        int min_index = -1;
        point inf_point = {st[top - 1].x, inf};
        for (int i = 0; i < n; i++)
        {
            if (dis(p[i], st[top - 1]) < eps) // avoid same point
                continue;
            long double this_angle = clockwise_angle(st[top - 1], inf_point, p[i]);
            if (this_angle < -eps || this_angle > pi - eps)
                // avoid many point in the most right/left line
                continue;
            if (this_angle < min_angle)
            {
                min_angle = this_angle;
                min_index = i;
            }
        }
        if (min_index == -1)
            break;
        st[top++] = p[min_index];
    }
    // lower hull
    while (1)
    {
        long double min_angle = inf;
        int min_index = -1;
        point inf_point = {st[top - 1].x, -inf};
        for (int i = 0; i < n; i++)
        {
            if (dis(p[i], st[top - 1]) < eps) // avoid same point
                continue;
            long double this_angle = clockwise_angle(st[top - 1], inf_point, p[i]);
            if (this_angle < -eps || this_angle > pi - eps)
                // avoid many point in the most right/left line
                continue;
            if (this_angle < min_angle)
            {
                min_angle = this_angle;
                min_index = i;
            }
        }
        if (min_index == -1)
            break;
        st[top++] = p[min_index];
    }
}
