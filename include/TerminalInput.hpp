#ifndef TERMINAL_INPUT_HPP
#define TERMINAL_INPUT_HPP


// #include "Game.hpp"
class Game;
#include <utility>

#include "TerminalOutput.hpp"
#include "ship.hpp"


enum class action
{
    attack,
    ability,
    save,
    load,
    restart, 
    exit,
    err,
};

class TerminalInput
{
private:
    TerminalInput();
    TerminalOutput output = TerminalOutput::instance();
protected:
    const std::string default_keybinds = "./utils/default_keybinds.json";
    const std::string custom_keybinds = "./utils/custom_keybinds.json";

    friend class BattleState;
    friend class Game;

    std::unordered_map<char, action> keybinds;
    std::unordered_map<std::string, action> necessary_keybinds = {
        {"attack", action::attack},
        {"ability", action::ability},
        {"save", action::save},
        {"load", action::load},
        {"start_new_game", action::restart},
        {"exit", action::exit}
    };
    bool getX(int& x);
    bool getXY(int& x, int& y);
    bool getXYR(int& x, int& y, bool& h);
    void checkKeybinds() const;

public:
    const std::string getString() const;
    static TerminalInput& instance();
    action getAction();

    std::pair<int, int> getFieldSize();
    int getShipSize();
    std::pair<int, int> getCoordinates();
    int getShipIndex();
    std::tuple<int, int, bool> getShipPlacement();

    
    friend std::istream& operator>>(std::istream& is, TerminalInput& game_input);
};

std::istream& operator>>(std::istream& is, TerminalInput& game_input);


#endif // TERMINAL_INPUT_HPP