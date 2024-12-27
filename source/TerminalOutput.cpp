#include "TerminalOutput.hpp"
#include "field.hpp"
#include "shipmanager.hpp"


TerminalOutput& TerminalOutput::instance() {
    static TerminalOutput self;
    return self;
}

void TerminalOutput::abilityMsg(AbilityStatus ability_type) {
    switch (ability_type)
    {
        case AbilityStatus::DoubleDamage:
        {
            std::cout << "You have double damage!\n";
            break;
        }
        case AbilityStatus::Scanner:
        {
            std::cout << "You have scanner!\nEnter coordinates to scan\n";
            break;
        }
        case AbilityStatus::Shelling:
        {
            std::cout << "You have shelling!\n";
            break;
        }
        default:
            std::cout << "Unknown Ability\n";
    }
}

void TerminalOutput::scannerMsg(AbilityStatus ability_type, int scanner_result) {
    if (scanner_result) {
        std::cout << "Segments found: " << scanner_result << "\n"; 
    }
    else {
        std::cout << "Segments not found\n";
    }
}

void TerminalOutput::logMsg(const std::string& msg) {
    std::cout << msg << '\n';
}

void TerminalOutput::displayPlayerField(GameField& field) {
    std::cout << "YOUR FIELD:\n";
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            if (field.hasShip(x, y)) { 
                if (field.getShipSegmentStatus(x, y) == ShipState::intact) {
                    std::cout << "[2]";
                } else if (field.getShipSegmentStatus(x, y) == ShipState::damaged) {
                    std::cout << "[1]";
                } else {
                    std::cout << "[0]";
                }
            }
            else if (field.getStatus(x, y) == CellStatus::unknown) {
                std::cout << "[ ]";
            } else if (field.getStatus(x, y) == CellStatus::empty) {
                std::cout << "[.]";
            }   
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void TerminalOutput::displayBotField(GameField& field) {
    std::cout << "BOT'S FIELD: \n";
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getHeight(); x++) {
            if (field.getStatus(x, y) == CellStatus::unknown) {
                std::cout << "[ ]";
            } else if (field.getStatus(x, y) == CellStatus::empty) {
                std::cout << "[.]";
            } else {
                if (field.getShipSegmentStatus(x, y) == ShipState::intact) {
                    std::cout << "[2]";
                } else if (field.getShipSegmentStatus(x, y) == ShipState::damaged) {
                    std::cout << "[1]";
                } else {
                    std::cout << "[0]";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void TerminalOutput::displayFields(GameField& player_field, GameField& bot_field) {
    displayPlayerField(player_field);
    std::cout << '\n';
    displayBotField(bot_field);
}

void TerminalOutput::displayShipManager(ShipManager& ship_manager) {
    int quantity = 1;
    std::vector<Ship*> ships = ship_manager.getShips();
    std::cout << "YOUR SHIPS: \n";
    for (auto ship : ships) {
        std::cout << "Ship №" << quantity++ << ": ";
        for (int i = 0; i < ship->getLength(); i++) {
            switch (ship->getSegmentState(i)){
                case (ShipState::intact):
                    std::cout << "[2]";
                    break;
                case (ShipState::damaged):
                    std::cout << "[1]";
                    break;
                default:
                    std::cout << "[0]";
            }
        }
        std::cout << "  Status: ";
        if (ship->isDestroyed()){
            std::cout << "Destroyed.\n";
        }
        else {
            std::cout << "Alive.\n";
        }
    }
}