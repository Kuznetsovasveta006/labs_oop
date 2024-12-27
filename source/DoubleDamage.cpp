#include "DoubleDamage.hpp"

DoubleDamageSettings::DoubleDamageSettings(GameField& field)
    : field(field)
{}

DoubleDamage::DoubleDamage(GameField& field)
    : field(field)
{}

AbilityStatus DoubleDamageSettings::getAbilityStatus() {
    return AbilityStatus::DoubleDamage;
}

void DoubleDamageSettings::acceptVisitor(Visitor& visitor) {
    visitor.visit(this);
}

void DoubleDamage::cast() {
    field.setDoubleAttack();
}