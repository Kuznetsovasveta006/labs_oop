#include "scanner.hpp"

#include <stdexcept>

ScannerSettings::ScannerSettings(GameField& field, int x, int y, int& result)
    : field(field), x_coord(x), y_coord(y), result(result)
{}

Scanner::Scanner(GameField& field, int x, int y, int& result)
    : field(field), x_coord(x), y_coord(y), result(result)
{}

AbilityStatus ScannerSettings::getAbilityStatus() {
    return AbilityStatus::Scanner;
}

void ScannerSettings::acceptVisitor(Visitor& visitor) {
    visitor.visit(this);
}

void Scanner::cast() {
    for (int j = y_coord; j < y_coord+2; j++){
        for (int i = x_coord; i < x_coord+2; i++) {
            if (field.checkCoords(i, j)) {
                if (field.hasShip(i, j)){
                    result++;
                }
            }
        }
    }
}