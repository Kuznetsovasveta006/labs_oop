#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP


#include "Game.hpp"
#include "GameCycle.hpp"
#include <map>


template <class Input, class Displayer>
class GameController
{
public:
    GameController(GameCycle& game);
    void run();
private:
    GameCycle& curr_session;
    Input input = Input::instance();
    Displayer output = Displayer::instance();
    std::map<action, std::function<void()>> actions; 
};

template <class Input, class Displayer>
GameController<Input, Displayer>::GameController(GameCycle& game)
    : curr_session(game), output(game)
{
    actions[action::attack] = [&](){curr_session.playerAttack();};
    actions[action::ability] = [&](){curr_session.castAbility();};
    actions[action::load] = [&](){curr_session.load();};
    actions[action::save] = [&](){curr_session.save();};
    actions[action::exit] = [&](){curr_session.exit();};
}

template<class Input, class Displayer>
void GameController<Input, Displayer>::run()
{
    curr_session.startNewGame();

    // while (!curr_session.bot_win)
    while (true)
    {
        output.displayMsg("Enter your move");
        auto act = input.getAction();
        if (actions.find(act) != actions.end())
        {
            actions[act]();
        }
        else
        {
            output.displayMsg("Unknown action");
        }

        if (curr_session.isPlayerStep()) 
        {
            curr_session.checkGameState();
            output.display();
            continue;
        }

        curr_session.botAttack();
        curr_session.checkGameState();
        output.display();
    }
}


#endif // GAME_CONTROLLER_HPP