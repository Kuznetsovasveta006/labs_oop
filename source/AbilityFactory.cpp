#include "AbilityFactory.hpp"


Ability* AbilityFactory::getAbility() {
    return builded_ability;
}

void AbilityFactory::buildDoubleDamage(DoubleDamageSettings* settings) {
    builded_ability = new DoubleDamage(settings->field);
}

void AbilityFactory::buildScanner(ScannerSettings* settings) {
    builded_ability = new Scanner(settings->field, settings->x_coord, settings->y_coord, settings->result);
}

void AbilityFactory::buildShelling(ShellingSettings* settings) {
    builded_ability = new Shelling(settings->ship_manager);
}
