#pragma once
#include "GameObject.h"

#include <memory>
#include <vector>

enum class FlowerType
{
    FlowerA,
    FlowerB,
    FlowerC,
    FlowerD,
    FlowerE
};

class Flower : public GameObject
{
    public:
        Flower(Texture2D texture, FlowerType type, Vector2 position, Vector2 scale = {1.0f, 1.0f});
        ~Flower() override {};
};