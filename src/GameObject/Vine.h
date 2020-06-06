#pragma once
#include "GameObject.h"

#include <memory>
#include <vector>

class Vine : public GameObject
{
    public:
        Vine(Texture2D texture, Vector2 position, Vector2 scale = {1.0f, 1.0f});
        ~Vine() override {};
};