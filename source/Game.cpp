#include "Game.hpp"
#include "field.hpp"
#include "shipmanager.hpp"
#include "GameState.hpp"


Game::Game() :
    round(0),
    is_player_step(true),
    player(nullptr),
    bot(nullptr) {}

Game::Game(Player* player) :
    round(0),
    is_player_step(true),
    player(player) {
    bot = new Bot(player->ship_manager.getShipSizes(), player->field.getWidth(), player->field.getHeight());
}
Game::Game(Player* player, Bot* bot, int round, bool player_step) :
    round(round),
    is_player_step(player_step),
    player(player),
    bot(bot)
{}

Game::Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships) :
    round(0),
    is_player_step(true),
    player(player) {
    bot = new Bot(size_bot_ships, width_bot, height_bot);
}

Game::Game(const Game& other) {
    player = other.player;
    bot = other.bot;
    is_player_step = other.is_player_step;
    round = other.round;
}

Game& Game::operator=(const Game& other) {
    if (this != &other) {
        player = other.player;
        bot = other.bot;
        is_player_step = other.is_player_step;
        round = other.round;
    }
    return *this;
}

bool Game::playerAttack(int x, int y) {
    bool flag = false;
    try {
        flag = bot->field.attack(x, y);
    }
    catch (const AttackCoordinatesError& e) {
        output.logMsg(e.what());
    }
    if (flag) {
        player->ability_manager.addAbility();
        output.logMsg("Added new ability\n");
    }
    if (bot->ship_manager.getAliveShips() == std::vector<Ship*>{}) {
        return true;
    }
    return false;
}

void Game::playerUseAbility(AbilitySettings& settings) {
    try {
        player->ability_manager.useAbility(settings);
    }
    catch (const NoAbilityError& e) {
        output.logMsg(e.what());
    }
}

bool Game::botAttack() {
    bool is_right_coords = false;
    int x;
    int y;
    while (!is_right_coords) {
        x = rand() % player->field.getWidth();
        y = rand() % player->field.getHeight();
        is_right_coords = true;
        if (player->field.getStatus(x, y) == CellStatus::empty) {
            is_right_coords = false;
        }
        else if (player->field.hasShip(x, y) && player->field.getShipSegmentStatus(x, y) == ShipState::destroyed) {
            is_right_coords = false;
        }
    }
    player->field.attack(x, y);
    if (player->ship_manager.getAliveShips() == std::vector<Ship*>{}) {
        return true;
    }
    return false;
}

bool Game::isPlayerStepNow() {
    return is_player_step;
}

void Game::takeTurn() {
    is_player_step = !is_player_step;
}

int Game::getRound() {
    return round;
}

Player& Game::getPlayer() {
    return *player;
}

Bot& Game::getBot() {
    return *bot;
}

void Game::newRound() {
    round += 1;
    std::vector<int> bot_ships = bot->ship_manager.getShipSizes();
    int width = bot->field.getWidth();
    int height = bot->field.getHeight();
    delete bot;
    bot = new Bot(bot_ships, width, height);
}