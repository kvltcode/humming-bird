#include "Background.h"
#include "Global.h"

Background::Background()
{
    mTexture = LoadTexture("resources/background-vine.png"); //800 x 542
    
    for (int i = 0; i < 3; ++i)
    {
        mBackgroundVines.push_back(std::make_unique<BackgroundVine>(mTexture, Vector2{static_cast<float>(mTexture.width) * i, 0.0f}));
    }    
}

Background::~Background()
{
    UnloadTexture(mTexture);
}

void Background::render()
{
    for (auto& vine: mBackgroundVines)
    {
        vine->render();
    }
}

void Background::update(float delta)
{
    for (auto& vine : mBackgroundVines)
    {    
        vine->incrementPosition(Vector2{-(vine->getVelocity() * delta), 0.0f});
    }

    if ((mBackgroundVines.front()->getPosition().x + mBackgroundVines.front()->getWidth()) <= 0.0f)
    {
        mBackgroundVines.pop_front();
        float positionX = mBackgroundVines.back()->getPosition().x + mBackgroundVines.back()->getWidth();
        mBackgroundVines.push_back(std::make_unique<BackgroundVine>(mTexture, Vector2{positionX, 0.0f}));
    }
}