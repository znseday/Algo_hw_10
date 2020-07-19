#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <string>
#include <vector>

extern bool IsDebugOutput;

#define MY_DEBUG_ONLY(x) { if(IsDebugOutput) {x}  }

class MyGraph
{
protected:

    int **G = nullptr;
    size_t N = 0;

public:
    MyGraph() = default;

    bool LoadFromFile(std::string fn);

    void Clear();
    ~MyGraph();

    void PrintAsMatrix();

    std::vector<std::vector<int>> Sort();
};

#endif // MYGRAPH_H
