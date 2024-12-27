#include "AbilityVisitor.hpp"


AbilityVisitor::AbilityVisitor(AbilityFactory& factory)
    : factory(factory)
{}

void AbilityVisitor::visit(class DoubleDamageSettings* settings) {
    factory.buildDoubleDamage(settings);
}

void AbilityVisitor::visit(class ScannerSettings* settings) {
    factory.buildScanner(settings);
}

void AbilityVisitor::visit(class ShellingSettings* settings) {
    factory.buildShelling(settings);
}