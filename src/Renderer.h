#pragma once
#include "Common.h"

class Renderer
{
public:
    Renderer(int w, int h);
    ~Renderer();
    void Run();

private:
    int mViewportWidth;
    int mViewportHeight;

    uint32_t* mBuffer = nullptr;
};
