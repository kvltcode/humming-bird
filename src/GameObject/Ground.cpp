#include "Ground.h"
#include "Global.h"

Ground::Ground(Texture2D texture, Vector2 position, Vector2 scale):
GameObject(texture, position, scale)
{
    //1280 x 77
    mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x, position.y + (7 * scale.y) , 1280 * scale.x, 70 * scale.y));

    mVelocity = 300.0f;
}