#include "Renderer.h"
#include "Common.h"
#include <MiniFB.h>
#include <thread>

Renderer::Renderer(int w, int h)
    : mViewportWidth(w)
    , mViewportHeight(h)
{
    mCurrentPixelIndex = 0;
}

Renderer::~Renderer() {}

void Renderer::Run()
{
    struct mfb_window *window = mfb_open_ex("my display", mViewportWidth, mViewportHeight, MFB_WF_RESIZABLE);
    if (window == NULL)
        return ;

    mBuffer = (uint32_t*)malloc(mViewportWidth * mViewportHeight * 4);

    // std::thread rendererThread(&Renderer::RunRendererThread, this);
    // rendererThread.detach();

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> rendererThreads(numThreads);
    for(int i = 0; i < numThreads; i++) {
        rendererThreads[i] = std::thread(&Renderer::RunRenderThread, this);
        rendererThreads[i].detach();
    }

    mfb_update_state state;
    do {
        // TODO: add some fancy rendering to the buffer

        state = mfb_update_ex(window, mBuffer, mViewportWidth, mViewportHeight);

        if (state != MFB_STATE_OK)
            break;

    } while(mfb_wait_sync(window));

    free(mBuffer);
    mBuffer = NULL;
    window = NULL;

    return ;
}

Color Renderer::RenderPixel(int x, int y)
{
    int t = 100000;
    while(t--);
    return {2550.f, 0.0f, 0.0f};
}

void Renderer::RunRenderThread()
{
    while(true) {
        int pixelIndex = mCurrentPixelIndex++;
        if(pixelIndex >= mViewportWidth * mViewportHeight)
            break;
        
        int x = pixelIndex % mViewportWidth;
        int y = pixelIndex / mViewportWidth;

        Color color = RenderPixel(x, y);
        uint32_t r = glm::clamp((uint32_t)glm::round(color.r * 255.0f), 0u, 255u);
        uint32_t g = glm::clamp((uint32_t)glm::round(color.g * 255.0f), 0u, 255u);
        uint32_t b = glm::clamp((uint32_t)glm::round(color.b * 255.0f), 0u, 255u);
        mBuffer[y * mViewportWidth + x] = (r << 16) | (g << 8) | (b);
    }
}
