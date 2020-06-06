#include "Player.h"

///@todo- - remove hardcoding
Player::Player(Texture2D texture, Vector2 position, Vector2 scale):
GameObject(texture, position, scale),
mStartPos(position)
{
    //100, 100
    //make bounding box a lot smaller. or multiple
    mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x  + (29 * scale.x), position.y  + (36 * scale.x), 42.0f * scale.x, 30.0f * scale.y));

    mFrameRect = { mCurrentFrame * 100.0f * scale.x, 
                   0, 
                   100.0f * scale.x, 
                   100.0f * scale.y };

    /*
    float x;
    float y;
    float width;
    float height;
    */
    mVelocity = 0;

    mParticleGenerator = std::make_unique<ParticleGenerator>(LoadTexture("resources/particle.png"), 30, 30, 150, 3.0f);
}

void Player::update(float delta)
{
    mFrameTime += delta;
    if (mFrameTime >= mFrameSpeed)
    {
        incrementFrame();
        mFrameTime = 0;
    }

    incrementPosition(Vector2{0.0f, delta * mVelocity});

    mParticleGenerator->update(delta, Vector2{mBoundingRects.at(0)->getCentreX(), mBoundingRects.at(0)->getCentreY()});
        
}
void Player::incrementFrame()
{
    ++mCurrentFrame;
    if (mCurrentFrame > mMaxFrames)
    {
        mCurrentFrame = 0;
    }

    //needs scale
    mFrameRect.x = mCurrentFrame * 100.0f;
}

void Player::setFrame(unsigned int frame)
{
    if(frame <= mMaxFrames)
    {
        mCurrentFrame = frame;
    }
}


void Player::reset()
{
    mPosition = mStartPos;
    mCurrentFrame = 0;
    mVelocity = 0;
    for (auto& hitbox : mBoundingRects)
    {
        hitbox->updateX(mPosition.x + 29); //need less hardcoding. more scaling
        hitbox->updateY(mPosition.y + 36); //need less hardcoding. more scaling
    }

    mCurrentFrame = 0;
    mFrameRect.x = mCurrentFrame * 100.0f;
    mParticleGenerator->clear();
}

void Player::render()
{
    mParticleGenerator->render();
	//DrawTexture(mTexture, mPosition.x, mPosition.y, WHITE);

    //DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);
    DrawTextureRec(mTexture, mFrameRect, mPosition, WHITE);  // Draw part of the texture

	if (Global::drawBoundingBoxes)
	{
		for (auto& boundingRect : mBoundingRects)
		{
			DrawRectangleLines(static_cast<int>(boundingRect->getLeft()), static_cast<int>(boundingRect->getTop()), static_cast<int>(boundingRect->getWidth()), static_cast<int>(boundingRect->getHeight()), BLACK);
		}
	}

       //DrawRectangle(mPosition.x, mPosition.y, mTexture.width, mTexture.height, MAROON);
};    