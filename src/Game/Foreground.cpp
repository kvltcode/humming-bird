#include "Foreground.h"
#include "Global.h"

#include <iostream> //temp

Foreground::Foreground()
{
    mTextures["ground"] = LoadTexture("resources/ground.png"); //1280 x 77
    mTextures["vine"] = LoadTexture("resources/vine.png"); //256, 383
    mTextures["flower1"] = LoadTexture("resources/flower1.png"); //234, 300
    mTextures["flower2"] = LoadTexture("resources/flower2.png"); //279, 300
    mTextures["flower3"] = LoadTexture("resources/flower3.png"); //393, 300
    mTextures["flower4"] = LoadTexture("resources/flower4.png"); //425, 300
    mTextures["flower5"] = LoadTexture("resources/flower5.png"); //145, 300

    mVines.push_back(std::make_unique<Vine>(mTextures["vine"], Vector2{0.0f, -80.0f}));
    mVines.push_back(std::make_unique<Vine>(mTextures["vine"], Vector2{500.0f, -80.0f}));
    mVines.push_back(std::make_unique<Vine>(mTextures["vine"], Vector2{1000.0f, -80.0f}));

    float xPosition = 0.0f;
    for (int i = 0; i < 5; ++i)
    {
        xPosition += 500;        
        int type = Random::GetInstance().drawNumber(1, 5);
        addFlower(type, xPosition);
    }
    
    for (int i = 0; i < 3; ++i)
    {
        mGround.push_back(std::make_unique<Ground>(mTextures["ground"], Vector2{ static_cast<float>(mTextures["ground"].width)* i, Global::screenHeight  - 70.0f}));
    }
}

Foreground::~Foreground()
{
    for (auto& texture: mTextures)
    {
        UnloadTexture(texture.second);
    }
    mTextures.clear();
}

void Foreground::addFlower(int type, float xPosition)
{
    float scale = Random::GetInstance().drawNumber(0.7f, 1.0f);
    float yPosition = Global::screenHeight - (320 * scale);

    switch(type)
    {
        case 1:
            mFlowers.push_back(std::make_unique<Flower>(mTextures["flower1"], FlowerType::FlowerA, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
        break;
        case 2:
            mFlowers.push_back(std::make_unique<Flower>(mTextures["flower2"], FlowerType::FlowerB, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
        break;
        case 3:
           mFlowers.push_back(std::make_unique<Flower>(mTextures["flower3"], FlowerType::FlowerC, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
        break;
        case 4:
            mFlowers.push_back(std::make_unique<Flower>(mTextures["flower4"], FlowerType::FlowerD, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
        break;
        case 5:
            mFlowers.push_back(std::make_unique<Flower>(mTextures["flower5"], FlowerType::FlowerE, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
        break;
        default:
            mFlowers.push_back(std::make_unique<Flower>(mTextures["flower1"], FlowerType::FlowerA, Vector2{xPosition, yPosition}, Vector2{scale, scale}));
            break;
    }
}

void Foreground::render()
{
    for (auto& ground : mGround)
    {
        ground->render();
    }

    for (auto& vine : mVines)
    {
        vine->render();
    }

    for (auto& flower : mFlowers)
    {
        flower->render();
    }
}

void Foreground::update(float delta)
{
    for (auto& ground : mGround)
    {
        ground->incrementPosition(Vector2{ -(ground->getVelocity() * delta), 0.0f });
    }

    if ((mGround.front()->getPosition().x + mGround.front()->getWidth()) <= 0.0f)
    {
        mGround.pop_front();
        float positionX = mGround.back()->getPosition().x + mGround.back()->getWidth();
        mGround.push_back(std::make_unique<Ground>(mTextures["ground"], Vector2{ positionX, Global::screenHeight - 70.0f }));
    }

    for (auto& vine : mVines)
    {
        vine->incrementPosition(Vector2{-(vine->getVelocity() * delta), 0.0f});
    }

    if (!mVines.empty())
    {
        if ((mVines.at(0)->getPosition().x + mVines.at(0)->getWidth()) <= 0)        
        {
            mVines.pop_front();
            float scale = Random::GetInstance().drawNumber(0.8f, 1.0f);            
            float yPosition = Random::GetInstance().drawNumber(50.0f, 100.0f);            
            yPosition *= -1.0f;
            mVines.push_back(std::make_unique<Vine>(mTextures["vine"], Vector2{static_cast<float>(Global::screenWidth), yPosition}, Vector2{scale, scale}));
        }
    }

    for (auto& flower : mFlowers)
    {
        flower->incrementPosition(Vector2{-(flower->getVelocity() * delta), 0.0f});
    }

    if (!mFlowers.empty())
    {
        if ((mFlowers.at(0)->getPosition().x + mFlowers.at(0)->getWidth()) <= 0)  
        {
            mFlowers.pop_front();           
            
            float xPosition = mFlowers.back()->getPosition().x + mFlowers.back()->getWidth() + 140;
            
            int type = Random::GetInstance().drawNumber(1, 5);
            
            addFlower(type, xPosition);            
        }
    }
}

bool Foreground::checkCollision(std::unique_ptr<BoundingRect>& target)
{
    bool result = false;

    //vines
    for (auto& vine : mVines)
    {
        //maybe throw this in the object class        
        auto& hitBoxs = vine->getBoundingRects();
        for (auto& hitBox : hitBoxs)
        {
            if(AABB(target, hitBox))
            {
                std::cout << "Hit the vine\n";
                return true;
            }
        }       
    }

    //flowers
    for (auto& flower : mFlowers)
    {
        //maybe throw this in the object class        
        auto& hitBoxs = flower->getBoundingRects();
        for (auto& hitBox : hitBoxs)
        {
            if(AABB(target, hitBox))
            {
                std::cout << "Hit the flower\n";
                return true;
            }
        }       
    }

    //ground
    for (auto& ground : mGround)    
    {
        auto& hitBoxs = ground->getBoundingRects();
        for (auto& hitBox : hitBoxs)
        {
            if(AABB(target, hitBox))
            {
                std::cout << "Hit the ground\n";
                return true;
            }
        }   
    }

    //std::cout << "Hit nothing\n";
    return false;
}

bool Foreground::AABB(std::unique_ptr<BoundingRect>& a, std::unique_ptr<BoundingRect>& b)
{
    bool collisionX =  a->getRight() >= b->getLeft()
			                && a->getLeft() <= b->getRight();

	bool collisionY =  a->getBottom() >= b->getTop()
			                && a->getTop() <= b->getBottom();

    if (collisionX && collisionY)
    {
        //std::cout << "Hit!\n";
	    return true;
    }

    //std::cout << "No hit\n";
    return false;
}