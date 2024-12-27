#include "shipmanager.hpp"


ShipManager::ShipManager(std::vector<int> ship_sizes) {
    for (auto& ship_size : ship_sizes)
    {
        auto ship_ptr = new Ship(ship_size);
        ships.push_back(ship_ptr);
    }
}

ShipManager::ShipManager(const ShipManager& other)
    : ships(other.ships)
{}

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) ships = other.ships;

    return *this;
}

ShipManager::~ShipManager() {
    for (Ship* ship : ships) {
        delete ship;
    }
}

int ShipManager::getShipsNumber() {
    return ships.size();
}

Ship& ShipManager::getShip(int index) {
    if (index < 0 or index >= static_cast<int>(ships.size())) {
        throw std::out_of_range("Ship index out of range");
    } 
    return *ships[index];
}

std::vector<Ship*> ShipManager::getAliveShips() {
    std::vector<Ship*> alive_ship;
    for (Ship* ship : ships) {
        if (!ship->isDestroyed()) {
            alive_ship.push_back(ship);
        }
    }
    return alive_ship;
}

std::vector<Ship*> ShipManager::getShips() {
    std::vector<Ship*> all_ships;
    for (Ship* ship : ships) {
        if (!ship->isDestroyed()) {
            all_ships.push_back(ship);
        }
    }
    return all_ships;
}

std::vector<int> ShipManager::getShipSizes() {
    std::vector<int> sizes;
    for (auto ship : ships) {
        sizes.push_back(ship->getLength());
    }
    return sizes;
}

void ShipManager::printShips() const noexcept {
    int quantity = 1;
    std::cout << "ALL SHIPS: \n";
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