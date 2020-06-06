#include "Game.h"

#ifdef _DEBUG 
int main(void)
#else 
int WinMain(void)
#endif 
{
    Game game;
    bool run = true;

    while (run)
    {
        run = game.handleInput();
        game.update();
        game.render();
    }

    return 0;
}