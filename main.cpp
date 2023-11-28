// test all these three algorithms
#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <string_view>
#include "graham.h"
#include "jarvis.h"
#include "marriage_before_conquest.h"

using namespace std;

vector<point> input_point;
string input_folder;

void refersh_in_out()
{
    fclose(stdout);
    fclose(stdin);
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
}

void set_in_out_to_target(int index)
{
    char input_file[100], output_file[100];

    // sprintf just like f-string in Python
    sprintf(input_file, "%s/convex_in_%d.txt", input_folder.c_str(), index);
    sprintf(output_file, "%s/out_%d.txt", input_folder.c_str(), index);
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
}

// amazing, this function do not work somehow, even cannot scanf...
long double test_alg_once(int index, string &alg, int times = 100)

// test one algotithm on one data case for 100 (default) times.
// alg in ["mbc", "graham", "jarvis"]
// gengrate input data first.

{
    set_in_out_to_target(index);

    int n;
    chrono::duration<double> duration = chrono::milliseconds::zero();
    vector<point> output_point;

    scanf("%d", &n);
    input_point.resize(n);
    // printf("%lf %lf", input_point[0].x, input_point[0].y);
    for (int i = 0; i < n; i++)
    {
        scanf("%Lf%Lf", &input_point[i].x, &input_point[i].y);
    }
    if (alg == "mbc")
    {
        Mbc mbc(input_point);
        vector<point> full_convex_line;
        for (int i = 0; i < times; i++)
        {

            mbc.points = input_point;
            auto start = chrono::high_resolution_clock::now();
            full_convex_line = mbc.mbc_full();
            auto end = chrono::high_resolution_clock::now();
            duration += end - start;
        }
        output_point = full_convex_line;
    }
    if (alg == "graham")
    {

        Graham gra(n);
        for (int i = 0; i < times; i++)
        {
            gra.p = input_point; // it is deep copy
            auto start = chrono::high_resolution_clock::now();
            gra.do_graham();
            auto end = chrono::high_resolution_clock::now();
            duration += end - start;
        }
        gra.st.resize(gra.top);
        output_point = gra.st;
    }
    if (alg == "jarvis")
    {
        Jarvis jar(n);
        for (int i = 0; i < times; i++)
        {
            jar.p = input_point;
            auto start = chrono::high_resolution_clock::now();
            jar.do_jarvis();
            auto end = chrono::high_resolution_clock::now();
            duration += end - start;
        }
        jar.st.resize(jar.top);
        output_point = jar.st;
    }
    printf("number of points of convex (+1): %d\n", output_point.size());
    for (auto &it : output_point)
    {
        printf("%Lf %Lf\n", it.x, it.y);
    }
    refersh_in_out();
    return duration.count(); // to double
}

int main()
{
    ofstream output_file("output.txt");

    // alg in {"mbc", "graham", "jarvis"}
    string algs[] = {
        "mbc",
        "graham", 
        "jarvis",
    };
    
    string cases[] = {
        "rect_false",
        "rect_true",
        "parabolic",
        "cycle",
        //"custom",
    };
    int no_runs = 1;  

    for (auto test_case : cases)
    {
        input_folder = "text_files_" + test_case;

        for(auto alg : algs)
        {
            output_file << "log_2(n) | time | no. runs ("+alg+" "+test_case+")\n";
            for (int i = 0; i < 10; i++)
            {
                char output[100];
                auto time = test_alg_once(i, alg, no_runs);
                sprintf(output, "%d | %lf | %d\n", i+2, time, no_runs);
                output_file << output;
                printf("%d-th data case, %s, %s duration: %Lf s\n", i, alg.c_str(), test_case.c_str(), time);
                if(time > 3600) {
                    break;
                }
            }
            output_file << "\n";
        }
    }

    output_file.close();
    return 0;
}
