#include <iostream>

using namespace std;

#include "mygraph.h"

bool IsDebugOutput = true;

int main()
{
    MyGraph myGraph;

    if (!myGraph.LoadFromFile("test.txt"))
    {
        cerr << "file not found or can not be read" << endl;
        exit(0);
    }

    myGraph.PrintAsMatrix();

    auto res = myGraph.Sort();

    size_t layer = 0;
    for (const auto & v : res)
    {
        cout << "layer " << layer++ << ": ";
        for (const auto i : v)
            cout << i << "  ";
        cout << endl;
    }
    cout << endl;

    return 0;
}
