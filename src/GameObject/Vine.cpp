#include "Vine.h"

Vine::Vine(Texture2D texture, Vector2 position, Vector2 scale):
GameObject(texture, position, scale)
{
    //256, 383
    mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (36 * scale.x), position.y  + (21  * scale.y), 201 * scale.x, 165 * scale.y));
    mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (138 * scale.x), position.y + (3  * scale.y), 80 * scale.x, 365 * scale.y));

    mVelocity = 300;
}