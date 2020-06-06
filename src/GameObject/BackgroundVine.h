#pragma once
#include "GameObject.h"

#include <memory>
#include <vector>

class BackgroundVine : public GameObject
{
    public:
        BackgroundVine(Texture2D texture, Vector2 position, Vector2 scale = {1.0f, 1.0f});
        ~BackgroundVine() override {};
};