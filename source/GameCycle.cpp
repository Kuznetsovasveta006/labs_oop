#include "GameCycle.hpp"
#include "GameState.hpp"
#include "Player.hpp"

GameCycle::GameCycle(Game game) :
    game(game)
{}
    
void GameCycle::startNewGame()
{
    bot_win = false;
    player_win = false;
    output.logMsg("Welcome!");
    output.logMsg("Press [l] to load or anything else to continue");
    if (input.getAction() == action::load)
    {
        load();
        output.displayFields(game.getPlayer().field, game.getBot().field);
        return;
    }

    auto [field_x, field_y] = game.input.getFieldSize();
    GameField* field = new GameField(field_x, field_y);

    int ship_num = game.input.getShipIndex();

    std::vector<int> ships;
    for (int i = 0; i < ship_num; ++i)
    {
        int ship_size = game.input.getShipSize();
        ships.push_back(ship_size);
    }

    ShipManager* ship_manager = new ShipManager(ships);
    AbilityManager* ability_manager = new AbilityManager();
    Player* player = new Player(*field, *ship_manager, *ability_manager);
    game = Game(player);

    for (int i = 0; i < ship_manager->getShipsNumber(); ++i) {
        game.output.displayPlayerField(game.getPlayer().field);
        game.output.displayShipManager(game.getPlayer().ship_manager);
        auto [x, y, r] = game.input.getShipPlacement();
        game.getPlayer().field.placeShip(ship_manager->getShip(i), x, y, r);
    }

    output.displayFields(game.getPlayer().field, game.getBot().field);
    output.logMsg("Game starts!");
};

void GameCycle::playerAttack()
{
    auto [x, y] = game.input.getCoordinates();

    try
    {
        player_win = game.playerAttack(x, y);
        game.takeTurn();
    }
    catch (const AttackCoordinatesError& e)
    {
        output.logMsg(e.what());
    }
}

void GameCycle::castAbility()
{
    std::cout << "Cast ability!\n";
    auto ability = game.getPlayer().ability_manager.getAvaliableAbility();
    game.output.abilityMsg(ability);
    switch (ability)
        {
            case AbilityStatus::DoubleDamage:
            {
                DoubleDamageSettings settings(game.getBot().field);
                game.playerUseAbility(settings);
                break;
            }
            case AbilityStatus::Scanner:
            {
                int scanner_result = 0;
                auto [x, y] = game.input.getCoordinates();
                ScannerSettings settings(game.getBot().field, x, y, scanner_result);
                game.playerUseAbility(settings);
                game.output.scannerMsg(ability, scanner_result);
                break;
            }
            case AbilityStatus::Shelling:
            {
                ShellingSettings settings(game.getBot().ship_manager);
                game.playerUseAbility(settings);
                break;
            }
            default:
                break;
        }
    take_turn_allowed = false;
}

void GameCycle::load() {
    game.output.logMsg("Enter savefile name");
    std::string file = game.input.getString();
    GameState gs(file);
    game = gs.load();
}

void GameCycle::save() {
    game.output.logMsg("Enter savefile name");
    GameState gs(game);
    std::string save = game.input.getString();
    gs.save(save);
    take_turn_allowed = false;
}

void GameCycle::exit() {
    std::cout << "Exit\n";
    std::terminate();
}

bool GameCycle::isPlayerStep() {
    return game.isPlayerStepNow();
}

void GameCycle::botAttack() {
    bot_win = game.botAttack();
}

void GameCycle::checkGameState() {
    if (player_win)
    {
        output.logMsg("You have won!");
        output.logMsg("Press [a] to start next round or any other key to exit");

        if (input.getAction() == action::attack)
        {
            player_win = false;
            bot_win = false;
            game.newRound();
        }
        else
        {
            this->exit();
        }
    }
    else if (bot_win)
    {
        output.logMsg("You have lost!");
        output.logMsg("Press [a] to start a new game or anu other key to exit");

        if (input.getAction() == action::attack)
        {
            player_win = false;
            bot_win = false;
            startNewGame();
        }
        else
        {
            this->exit();
        }
    }
}