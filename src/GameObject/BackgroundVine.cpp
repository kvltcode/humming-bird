#include "BackgroundVine.h"
#include "Global.h"

BackgroundVine::BackgroundVine(Texture2D texture, Vector2 position, Vector2 scale):
GameObject(texture, position, scale)
{
    //800 x 542
    mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x, position.y + (7 * scale.y) , 800 * scale.x, 542 * scale.y));

    mVelocity = 100.0f;
}