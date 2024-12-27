#ifndef ABILITY_FACTORY_HPP
#define ABILITY_FACTORY_HPP

#include "IAbility.hpp"
#include "DoubleDamage.hpp"
#include "scanner.hpp"
#include "shelling.hpp"


class AbilityFactory {
public:
    AbilityFactory() = default;

    Ability* getAbility();

    ~AbilityFactory() = default;
    
    void buildDoubleDamage(DoubleDamageSettings* settings);
    void buildScanner(ScannerSettings* settings);
    void buildShelling(ShellingSettings* settings);

private:
    Ability* builded_ability = nullptr;
};

#endif //ABILITY_FACTORY_HPP