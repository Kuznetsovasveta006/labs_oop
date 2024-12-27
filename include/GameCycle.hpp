#ifndef GAME_CYCLE_HPP
#define GAME_CYCLE_HPP

#include "Game.hpp"


class GameCycle {


public:
    bool player_win;
    bool bot_win;
    bool take_turn_allowed;
    TerminalInput input = TerminalInput::instance();
    TerminalOutput output = TerminalOutput::instance();
    Game game;
    
    GameCycle(Game game);

    ~GameCycle() = default;

    void startNewGame();
    void playerAttack();
    void castAbility();
    void load();
    void save();
    void exit();
    bool isPlayerStep();
    void botAttack();
    void checkGameState();
};


#endif // GAME_CYCLE_HPP
