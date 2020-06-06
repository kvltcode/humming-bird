#pragma once
#include "raylib.h"

class BoundingRect
{
    private:

        const float mWidth;
        const float mHeight;

        float mCentreX;
        float mCentreY;

        float mLeft;
        float mRight;
        float mTop;
        float mBottom;  

        void calculateBounds()
        {
            //float mTop; //only ones that are changed
            //float mLeft;  //only ones that are changed
            //float mWidth; //fixed
            //float mHeight; //fixed
            
            mRight = mLeft + mWidth;
            mBottom = mTop + mHeight;
            
            mCentreX = mLeft + (mWidth / 2.0f);
            mCentreY = mTop + (mHeight / 2.0f);
        }

    public:        
        BoundingRect(float left, float top, float width, float height):
        mLeft(left), mTop(top), mWidth(width), mHeight(height)
        {
            calculateBounds();
        }        

        void incrementPosition(const Vector2& position)
        {
            mLeft += position.x;
            mTop += position.y;
            calculateBounds();
        }

        void updateX(float x)
        {
            mLeft = x;            
            calculateBounds();
        }

        void updateY(float y)
        {
            mTop = y;
            calculateBounds();
        }

        float getCentreX() const { return mCentreX; }
        float getCentreY() const { return mCentreY; }
        float getWidth() const { return mWidth; }
        float getHeight() const { return mHeight; }

        float getLeft() const { return mLeft; }
        float getRight() const { return mRight; }
        float getBottom() const { return mBottom; }
        float getTop() const { return mTop; }
};