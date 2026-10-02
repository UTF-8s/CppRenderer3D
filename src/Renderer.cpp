#include "Renderer.h"
#include <MiniFB.h>

Renderer::Renderer(int w, int h)
    : mViewportWidth(w)
    , mViewportHeight(h) {}

Renderer::~Renderer() {}

void Renderer::Run()
{
    struct mfb_window *window = mfb_open_ex("my display", mViewportWidth, mViewportHeight, MFB_WF_RESIZABLE);
    if (window == NULL)
        return ;

    mBuffer = (uint32_t*)malloc(mViewportWidth * mViewportHeight * 4);

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
