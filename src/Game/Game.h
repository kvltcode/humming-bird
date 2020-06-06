#pragma once

#include "Player.h"
#include "Flower.h"
#include "raylib.h"
#include "BoundingRect.h"
#include "Screen.h"

#include "Global.h"
#include "Foreground.h"
#include "Background.h"


#include <memory>
#include <deque>

//Top left = 0,0
// --------------> +
// |
// |
// |
// V +

//also rects draw from that position
///circles don't
class Game
{

private:

	Screen mCurrentScreen = Screen::START;
	//Screen mCurrentScreen = Screen::MAIN;

	Texture2D mPlayerTexture;
	std::unique_ptr<Player> mPlayer;

	Texture2D mStartTexture;

    unsigned int mScore = 0;
	const unsigned int mMaxScore = 999999999;

	std::unique_ptr<Foreground> mForeground;
	std::unique_ptr<Background> mBackground;
	float mDelta = 0;

	void reset();

public:
	Game();
	~Game();

	bool handleInput();
	void update();
	void render();
};