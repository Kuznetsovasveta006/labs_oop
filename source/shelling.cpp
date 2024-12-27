#include "shelling.hpp"
#include <ctime>
#include <iostream>

ShellingSettings::ShellingSettings(ShipManager& manager)
    : ship_manager(manager)
{}

Shelling::Shelling(ShipManager& manager)
    : ship_manager(manager)
{}

AbilityStatus ShellingSettings::getAbilityStatus() {
    return AbilityStatus::Shelling;
}

void ShellingSettings::acceptVisitor(Visitor& visitor) {
    visitor.visit(this);
}

void Shelling::cast() {
    int shipsNumber = ship_manager.getShipsNumber();
    if (shipsNumber == 0) {
        throw std::logic_error("No ships");
    }
    int shipIndex = rand() % shipsNumber;
    Ship& randomShip = ship_manager.getShip(shipIndex);
    int randomSegmentIndex = rand() % randomShip.getLength();
    randomShip.damageSegment(randomSegmentIndex);
}