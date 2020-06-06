#include "Game.h"
#include <iostream>
#include <string>

Game::Game()
{
	InitWindow(Global::screenWidth, Global::screenHeight, "Humming Bird");
	SetTargetFPS(60);
	SetTraceLogLevel(3);
	Image icon = LoadImage("resources/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	mBackground = std::make_unique<Background>();

	mForeground = std::make_unique<Foreground>();

	mPlayerTexture = LoadTexture("resources/bird.png"); //400 / 100
	mPlayer = std::make_unique<Player>(mPlayerTexture, Vector2{Global::screenWidth / 4.0f, (Global::screenHeight / 2.0f) - (mPlayerTexture.height / 2.0f) });

	mStartTexture = LoadTexture("resources/start.png"); //1280 / 720

}

Game::~Game()
{
	UnloadTexture(mPlayerTexture);
	UnloadTexture(mStartTexture);

	CloseWindow(); // Close window and OpenGL context
}

///@todo Rewrite this
bool Game::handleInput()
{
	if (WindowShouldClose())
	{
		return false;
	}
	
 	mDelta = GetFrameTime();

	switch(mCurrentScreen)
	{
		case Screen::START:
		{
			if (IsKeyDown(KEY_ENTER))
			{	
				mCurrentScreen = Screen::MAIN;
			}
			break;
		}
		case Screen::MAIN:
		{
			if (IsKeyDown(KEY_D))
			{			
				bool okToMove = true;
				auto& hitboxes = mPlayer->getBoundingRects();			

				float maxWidth = Global::screenWidth / 2.0f;
				if(!Global::collisionsOn)
				{
					maxWidth = static_cast<float>(Global::screenWidth);
				}

				for (auto& hitbox : hitboxes)
				{
					if (hitbox->getRight() >= maxWidth)
					{
						okToMove = false;
					}
				}
				
				if (okToMove)
				{
					mPlayer->incrementPosition(Vector2{ 2.0f, 0.0f });
				}			
			}

			if (IsKeyDown(KEY_A))
			{
				bool okToMove = true;
				auto& hitboxes = mPlayer->getBoundingRects();			
				for (auto& hitbox : hitboxes)
				{
					if (hitbox->getLeft() <= 0)
					{
						okToMove = false;
					}
				}
				
				if (okToMove)
				{
					mPlayer->incrementPosition(Vector2{ -2.0f, 0.0f });
				}
			}

			if (IsKeyDown(KEY_S))
			{
				bool okToMove = true;
				auto& hitboxes = mPlayer->getBoundingRects();
				for (auto& hitbox : hitboxes)
				{
					if (hitbox->getBottom() >= Global::screenHeight)
					{
						okToMove = false;
					}
				}

				if (okToMove)
				{
					mPlayer->incrementPosition(Vector2{ 0.0f, 2.0f });
				}
			}

			if (!Global::collisionsOn)
			{
				if (IsKeyDown(KEY_W))
				{
					bool okToMove = true;
					auto& hitboxes = mPlayer->getBoundingRects();			
					for (auto& hitbox : hitboxes)
					{
						if (hitbox->getTop() <= 0)
						{
							okToMove = false;
						}
					}
					
					if (okToMove)
					{
						mPlayer->incrementPosition(Vector2{ 0.0f, -2.0f });
					}
				}				
			}
			
			if (IsKeyDown(KEY_SPACE))
			{
				if (Global::gravityOn)
				{
					mPlayer->setVelocity(-150);
				}
				mPlayer->setFrame(1);
			}

			if (IsKeyReleased(KEY_SPACE))
			{
				mPlayer->setFrame(3);
			}

			if (IsKeyReleased(KEY_F))
			{
				mPlayer->incrementFrame();				
			}

			break;
		}

		case Screen::GAMEOVER:
		{
			if (IsKeyDown(KEY_ENTER))
			{	
				reset();
				mCurrentScreen = Screen::MAIN;
			}
			break;
		}
	}

	return true;
}

void Game::update()
{
	if(mCurrentScreen == Screen::MAIN)
	{
		//plaer
		mPlayer->update(mDelta);

		if (Global::gravityOn)
		{
			if (mPlayer->getVelocity() < Global::gravity)
			{
				mPlayer->setVelocity(mPlayer->getVelocity() + (mDelta * Global::gravity));
			}
			else
			{
				mPlayer->setVelocity(Global::gravity);
			}
		}

		//score
		mScore += static_cast<int>((mDelta * Global::scoreIncrement));
		if (mScore > mMaxScore) { mScore = mMaxScore; }

		//background
		mBackground->update(mDelta);

		//foreground
		mForeground->update(mDelta);

		//collision detection
		if(Global::collisionsOn)
		{
			auto& hitBoxs = mPlayer->getBoundingRects();
			for (auto& hitBox : hitBoxs)
			{
				if(mForeground->checkCollision(hitBox) == true)
				{
					mCurrentScreen = Screen::GAMEOVER;
					return;
				}
			}		
		}
	}
}

void Game::render()
{
	BeginDrawing();

	ClearBackground(Color{ 247, 251, 251, 255 });

	switch (mCurrentScreen)
	{ 
		case Screen::START:
		{
			//background
			DrawTexture(mStartTexture, 0, 0, WHITE);

			//credits
			DrawText("Paul Hanson", 20, Global::screenHeight - 30, 24, BLACK);
		}
		break;

		case Screen::MAIN:
		{
			//background
			mBackground->render();

			//foreground
			mForeground->render();

			//player
			mPlayer->render();

			//score
			std::string score = "Score: " + std::to_string(mScore);
			int fontWidth = static_cast<int>(score.length() * 11); //not measuring the text here because the individual character width change
			DrawText(score.c_str(), Global::screenWidth - 80 - fontWidth, 20, 30, DARKGRAY);			
		}
		break;

		case Screen::GAMEOVER:
		{
			//background
			mBackground->render();

			//foreground
			mForeground->render();

			//player
			mPlayer->render();
			
			//score - figure out the size of the text so we can figure out the size of the background
			std::string label = "Final score: " + std::to_string(mScore);
			int fontSize = 50;
			int fontWidth = MeasureText(label.c_str(), fontSize);    

			//score background
			DrawRectangle((Global::screenWidth / 2.0f) - (fontWidth / 2.0f) - 22, (Global::screenHeight / 2.0f) - 122, fontWidth + 44, 164, DARKGRAY);
			DrawRectangle((Global::screenWidth / 2.0f) - (fontWidth / 2.0f) - 20, (Global::screenHeight / 2.0f) - 120, fontWidth + 40, 160, WHITE);
			DrawText(label.c_str(), (Global::screenWidth / 2.0f) - (fontWidth / 2.0f),  (Global::screenHeight / 2.0f) - 100, fontSize, DARKGRAY);

			//try again text
			label = "Press Enter to try again";
			fontSize = 30;
			fontWidth = MeasureText(label.c_str(), fontSize); 
			DrawText(label.c_str(),  (Global::screenWidth / 2.0f) - (fontWidth / 2.0f),  (Global::screenHeight / 2.0f) - 20, fontSize, DARKGRAY);
		}
		break;
	}

	if (Global::drawFPS)	
	{
		DrawFPS(Global::screenWidth- 100, 80);
	}

	EndDrawing();
}

void Game::reset()
{
	mScore = 0;
	mPlayer->reset();
}