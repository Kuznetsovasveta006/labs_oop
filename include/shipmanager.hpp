#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <iostream>   
#include <vector>   
#include <stdexcept>

#include "ship.hpp"


class ShipManager {   

public:
    ShipManager(const std::vector<int> ship_sizes);

    ShipManager(const ShipManager& other);

    ShipManager& operator=(const ShipManager& other);

    ~ShipManager();

    Ship& getShip(int index);

    std::vector<int> getShipSizes();

    std::vector<Ship*> getAliveShips();

    std::vector<Ship*> getShips();

    void printShips() const noexcept;

    int getShipsNumber();
   
private: 
    std::vector<Ship*> ships;
}; 


#endif //SHIPMANAGER_HPP