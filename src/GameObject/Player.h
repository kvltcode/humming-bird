#pragma once
#include "GameObject.h"
#include "ParticleGenerator.h"

#include <memory>
#include <vector>

class Player : public GameObject
{
    private:
        Vector2 mStartPos;
        Rectangle mFrameRect;
        const unsigned int mMaxFrames = 3; //start at zero
        unsigned int mCurrentFrame = 0;
        const float mFrameSpeed = 0.25;
        float mFrameTime = 0;

        std::unique_ptr<ParticleGenerator> mParticleGenerator;

    public:
        Player(Texture2D texture, Vector2 position, Vector2 scale = {1.0f, 1.0f});
        ~Player() override {};

        void update(float delta);

        float getVelocity() const { return mVelocity; }
        void setVelocity(float velocity) { mVelocity = velocity; }

        void incrementFrame();
        void setFrame(unsigned int frame);

        void reset();
        
        void render();
};