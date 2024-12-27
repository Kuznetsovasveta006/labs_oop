#include <exception>


#include "TerminalInput.hpp"
#include "FileHandler.hpp"
#include "ship.hpp"


TerminalInput::TerminalInput()
{
    try 
    {
        FileHandler fh(custom_keybinds);
        fh.openForRead();
        fh.read(*this);
    }
    catch (const std::exception& e)
    {
        output.logMsg(e.what());
        output.logMsg("Could not access custom keybinds. Default keybinds applied");
        FileHandler fh(default_keybinds);
        fh.openForRead();
        fh.read(*this);
    }
}

TerminalInput& TerminalInput::instance()
{
    static TerminalInput self;
    return self;
}

action TerminalInput::getAction()
{
    char inp;
    std::cin >> inp;

    auto it = keybinds.find(inp);
    if (it != keybinds.end())
    {
        return it->second;
    }
    else
    {
        return action::err;
    }
}


bool TerminalInput::getX(int& x)
{
    if (std::cin >> x)
    {
        return true;
    }

    return false;
}


bool TerminalInput::getXY(int& x, int& y)
{
    if (std::cin >> x >> y)
    {
        return true;
    }
    return false;
}


bool TerminalInput::getXYR(int& x, int& y, bool& r)
{
    std::string orientation = "";
    if (!(std::cin >> x >> y))
    {
        return false;
    }
    std::cin >> orientation;
    if (orientation == "h" or orientation == "hor" or orientation == "horizontal")
    {
        r = true;
        return true;
    }
    else if (orientation == "v" or orientation == "ver" or orientation == "vertical")
    {
        r = false;
        return true;
    }

    return false;
}

const std::string TerminalInput::getString() const 
{
    std::string inp;
    std::cin >> inp;
    return inp;
}

void TerminalInput::checkKeybinds() const 
{
    std::vector<action> actions;

    for (const auto& [key, action] : keybinds)
    {
        if (std::find(actions.begin(), actions.end(), action) != actions.end())
        {
            throw std::logic_error("Same key for multiple actions\n");
        }

        actions.emplace_back(action);
    }
}

std::istream& operator>>(std::istream& is, TerminalInput& game_input)
{
    json j;
    is >> j;

    for (const auto& [key, val]: j.items())
    {
        auto it = game_input.necessary_keybinds.find(val);
        if (it != game_input.necessary_keybinds.end())
        {
            game_input.keybinds[key[0]] = it->second;
        }
        else
        {
            throw std::logic_error("Unknown action keybind\n");
        }
    }

    if (game_input.keybinds.size() != game_input.necessary_keybinds.size())
    {
        throw std::logic_error("Unlawful key binds\n");
    }

    game_input.checkKeybinds();

    return is;
}

std::pair<int, int> TerminalInput::getCoordinates()
{
    output.logMsg("Choose a cell to attack!");
    int x = -1, y = -1;
    bool success = getXY(x, y);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Invalid coordinates! Try again");
        success = getXY(x, y);
    }

    return std::pair<int, int>(x, y);
}

std::pair<int, int> TerminalInput::getFieldSize()
{
    output.logMsg("Input field size");
    int x = -1, y = -1;
    bool success = getXY(x, y);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Invalid input. Enter two integers.");
        success = getXY(x, y);
    }

    return std::pair<int, int>(x, y);
}

int TerminalInput::getShipIndex()
{
    output.logMsg("Enter how many ships you would have:");
    int i = -1;
    bool success = getX(i);
    while (!success or i < 0)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Incorrect ship index! Enter a positive number like: 1");
        success = getX(i);
    }
    
    return i;
}

int TerminalInput::getShipSize()
{
    output.logMsg("Input ship size");
    int size = 1;
    bool success = getX(size);
    while (!success or size < 0)
    {
        output.logMsg("Incorrect ship size! Enter a positive number like: 1");
        success = getX(size);
    }

    return size;
}

std::tuple<int, int, bool> TerminalInput::getShipPlacement()
{
    output.logMsg("Place your ship!");
    int x = -1, y = -1;
    bool r = true;
    bool success = getXYR(x, y, r);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();
        
        output.logMsg("You can't place a ship like that! Try something like: 1, 2, h");
        success = getXYR(x, y, r);
    }

    return std::tuple<int, int, bool>(x, y, r);
}