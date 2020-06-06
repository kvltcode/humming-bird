#pragma once

#include "Random.h"

#include "Vine.h"
#include "Ground.h"
#include "Flower.h"

#include <deque>
#include <memory>
#include <unordered_map>

class Foreground
{
    private:
        
        std::unordered_map<std::string, Texture2D> mTextures;
        
        std::deque<std::unique_ptr<Vine>> mVines; //change this to and array and don't pop them
        std::deque<std::unique_ptr<Flower>> mFlowers;
        std::deque<std::unique_ptr<Ground>> mGround;
        
        void addFlower(int type, float xPositon);
        bool AABB(std::unique_ptr<BoundingRect>& a, std::unique_ptr<BoundingRect>& b);
    public:
        Foreground();
        ~Foreground();
        void render();
        void update(float delta);
        bool checkCollision(std::unique_ptr<BoundingRect>& target);
};