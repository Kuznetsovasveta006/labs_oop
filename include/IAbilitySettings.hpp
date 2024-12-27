#ifndef ABILITY_SETTINGS_HPP
#define ABILITY_SETTINGS_HPP

#include "IVisitor.hpp"


enum class AbilityStatus { DoubleDamage, Scanner, Shelling };

class AbilitySettings {
public:
    virtual AbilityStatus getAbilityStatus()=0;
    virtual void acceptVisitor(Visitor& visitor)=0;
};

#endif //ABILITY_SETTINGS_HPP