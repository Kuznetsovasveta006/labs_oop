#ifndef DOUBLE_DAMAGE_HPP
#define DOUBLE_DAMAGE_HPP

#include "IAbility.hpp"
#include "IAbilitySettings.hpp"
#include "field.hpp"

class DoubleDamageSettings: public AbilitySettings {
public:
    DoubleDamageSettings(GameField& field);

    AbilityStatus getAbilityStatus() override;

    void acceptVisitor(Visitor& visitor) override;

    GameField& field;
};

class DoubleDamage: public Ability {
public:
    DoubleDamage(GameField& field);  
    void cast() override;

private:
    GameField& field;
};

#endif // DOUBLE_DAMAGE_HPP