#ifndef GAME_HPP
#define GAME_HPP

#include "TerminalInput.hpp"
#include "TerminalOutput.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "AttackCoordinatesError.hpp"
#include "NoAbilityError.hpp"


class Game {
public:
    Game();

    Game(Player* player);

    Game(Player* player, Bot* bot, int round, bool player_step);

    Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships);

    Game(const Game& other);

    Game& operator=(const Game& other);

    ~Game() = default;

    bool playerAttack(int x, int y);

    void playerUseAbility(AbilitySettings& settings);

    bool botAttack();

    bool isPlayerStepNow();

    int getRound();

    Player& getPlayer();

    Bot& getBot();

    void newRound();

    void takeTurn();
 
    TerminalInput input = TerminalInput::instance();
    TerminalOutput output = TerminalOutput::instance();

private:
    int round;
    bool is_player_step;
    Player* player;
    Bot* bot;

    template <typename T1, typename T2>
    friend class GameController;

    template <typename T>
    friend class GameRenderer;

};

#endif // GAME_HPP