#include <iostream>
#include <fstream>
#include <algorithm>

#include "mygraph.h"

using namespace std;

bool MyGraph::LoadFromFile(std::string fn)
{
    ifstream f(fn);
    if (!f)
        return false;

    size_t Smax;

    f >> N >> Smax;

    int **A = new int*[N];

    for (size_t i = 0; i < N; ++i)
    {
        A[i] = new int[Smax];
        for (size_t j = 0; j < Smax; ++j)
        {
            f >> A[i][j];
        }
    }

    MY_DEBUG_ONLY(
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < Smax; ++j)
                cout << A[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
    )

    G = new int*[N];
    for (size_t i = 0; i < N; ++i)
    {
        G[i] = new int[N];
        for (size_t j = 0; j < N; ++j)
        {
            if ( any_of(A[i], A[i]+Smax, [j](int n){return (int)j==n;}) )
                G[i][j] = 1;
            else
                G[i][j] = 0;
        }
    }


    for (size_t i = 0; i < N; ++i)
        delete[]A[i];
    delete[]A;

    return true;
}
//-------------------------------------------------------------

void MyGraph::PrintAsMatrix()
{
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
            cout << G[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
//-------------------------------------------------------------

vector<vector<int>> MyGraph::Sort()
{
    vector<vector<int>> res;
    vector<int> M(N, 0);

    size_t layer = 0;

    for (size_t j = 0; j < N; ++j)
        for (size_t i = 0; i < N; ++i)
           M[j] += G[i][j];

    do
    {
        bool zeroExists = false;
        for (size_t i = 0; i < N; ++i)
        {
            if (M[i] == 0)
            {
                if (!zeroExists)
                {
                    res.emplace_back(vector<int>());
                    zeroExists = true;
                }

                res[layer].emplace_back(i);
                M[i] = -1;
            }
        }

        if (!zeroExists)
            break;

        for (const auto n : res[layer])
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (M[i] != -1)
                    M[i] -= G[n][i];
            }
        }

         layer++;

    } while (true);

    return res;
}
//-------------------------------------------------------------

void MyGraph::Clear()
{
    if (G)
    {
        for (size_t i = 0; i < N; ++i)
            delete[]G[i];
        delete[]G;
        G = nullptr;
    }

}
//-------------------------------------------------------------

MyGraph::~MyGraph()
{
    Clear();
}
//-------------------------------------------------------------










