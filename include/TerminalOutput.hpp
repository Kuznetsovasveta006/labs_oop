#ifndef TERMINAL_OUTPUT_HPP
#define TERMINAL_OUTPUT_HPP


#include <iostream>
#include <vector>
#include <unordered_map>

#include "IAbilitySettings.hpp"


class GameState;
class GameField;
class ShipManager;


class TerminalOutput
{
public:
    static TerminalOutput& instance();

    void abilityMsg(AbilityStatus ability_type);
    void scannerMsg(AbilityStatus ability_type, int scanner_result);
    void logMsg(const std::string& msg);
    void displayPlayerField(GameField& field);
    void displayBotField(GameField& field);
    void displayFields(GameField& player_field, GameField& bot_field);
    void displayShipManager(ShipManager& ship_manager);

private:
    TerminalOutput() = default;
};


#endif // TERMINAL_OUTPUT_HPP