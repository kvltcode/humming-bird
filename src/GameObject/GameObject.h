#pragma once
#include "raylib.h"
#include "Global.h"

#include "BoundingRect.h"

#include <memory>
#include <vector>

class GameObject
{
protected:
    Vector2 mPosition;
    Texture2D mTexture;

    int mWidth;
    int mHeight;    

    float mVelocity = 0;

	std::vector<std::unique_ptr<BoundingRect>> mBoundingRects;    

public:
    GameObject(Texture2D texture, Vector2 position, Vector2 scale = {1.0f, 1.0f}):
		mTexture(texture),
		mPosition(position) 
		{
			mTexture.width *= scale.x;
    		mTexture.height *= scale.y;

    		mWidth = mTexture.width;
    		mHeight = mTexture.height;
		};
		
	virtual ~GameObject() {};

	void render()
	{
		DrawTextureV(mTexture, mPosition, WHITE);

		if (Global::drawBoundingBoxes)
		{
			for (auto& boundingRect : mBoundingRects)
			{
				DrawRectangleLines(boundingRect->getLeft(), boundingRect->getTop(), boundingRect->getWidth(), boundingRect->getHeight(), BLACK);
			}
		}
	};    

	void incrementPosition(Vector2 position)
	{
		for (auto& boundingRect : mBoundingRects)
		{
			boundingRect->incrementPosition(position);
		}
		mPosition.x += position.x;
		mPosition.y += position.y;
	}

	std::vector<std::unique_ptr<BoundingRect>>& getBoundingRects() { return mBoundingRects; }

    float getVelocity() const { return mVelocity; }
    Vector2 getPosition() const { return mPosition; }
    const int  getWidth() const { return mWidth; }
    const int getHeight() const { return mHeight; }

};