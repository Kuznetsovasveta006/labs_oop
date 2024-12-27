#ifndef GAME_DISPLAYER_HPP
#define GAME_DISPLAYER_HPP


#include "GameCycle.hpp"


template <class Output>
class GameDisplayer
{
public:
    static GameDisplayer& instance(GameCycle& game)
    {
        static GameDisplayer self(game);
        return self;
    }
    void display();
    void displayMsg(const std::string& msg);

private:
    Output output = Output::instance();
    GameCycle& game;
    
    GameDisplayer(GameCycle& game): game(game) {};

    template <typename T1, typename T2>
    friend class GameController;
};

template <class Output>
void GameDisplayer<Output>::display()
{
    output.displayFields(game.game.getPlayer().field, game.game.getBot().field);
}


template <class Output>
void GameDisplayer<Output>::displayMsg(const std::string& msg)
{
    output.logMsg(msg);
}


#endif // GAME_DISPLAYER_HPP