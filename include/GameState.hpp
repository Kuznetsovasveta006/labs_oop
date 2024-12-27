#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <nlohmann/json.hpp>

// #include "Game.hpp"
#include "FileHandler.hpp"
class Game;
class GameField;
class ShipManager;
class AbilityManager;


using json = nlohmann::json;

class GameState {
private:
    json current_state;

public:
    GameState(Game& game);

    GameState(const std::string& file_name);
    
    ~GameState() = default;

    json saveFieldToJson(GameField& field);

    json saveShipsToJson(ShipManager& ship_manager);

    json saveAbilityManagerToJson(AbilityManager& ability_manager);

    bool save(const std::string& file_name);

    GameField loadFieldFromJson(int width, int height, json& field_data);
    
    ShipManager loadShipManagerFromJson(json& ship_data, GameField& field);

    AbilityManager loadAbilityManagerFromJson(json& ability_data);

    Game load();

    friend std::ostream& operator<<(std::ostream& os, GameState& state);

    friend std::istream& operator>>(std::istream& is, GameState& state);
};

#endif // GAME_STATE_HPP
