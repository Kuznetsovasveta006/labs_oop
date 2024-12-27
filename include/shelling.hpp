#ifndef SHELLING_HPP
#define SHELLING_HPP

#include "IAbility.hpp"
#include "IAbilitySettings.hpp"
#include "shipmanager.hpp"


class ShellingSettings: public AbilitySettings {
public:
    ShipManager ship_manager;

    ShellingSettings(ShipManager& manager);

    AbilityStatus getAbilityStatus() override;

    void acceptVisitor(Visitor& visitor) override;
};

class Shelling: public Ability {
public:
    Shelling(ShipManager& manager);

    void cast() override;

private:
    ShipManager ship_manager;
};

#endif // SHELLING_HPP