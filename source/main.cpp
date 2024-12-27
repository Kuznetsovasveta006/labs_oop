#include "Game.hpp"
#include "GameCycle.hpp"
#include "GameController.hpp"
#include "GameDisplayer.hpp"

int main()
{
    Game g;
    GameCycle gc(g);
    GameController<TerminalInput, GameDisplayer<TerminalOutput>> controller(gc);
    try 
    {
        controller.run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}