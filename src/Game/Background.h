#pragma once

#include "BackgroundVine.h"

#include <memory>
#include <deque>

class Background
{
    private:

        std::deque<std::unique_ptr<BackgroundVine>> mBackgroundVines;
        Texture2D mTexture;

    public:
        Background();
        ~Background();
        void render();
        void update(float delta);
};