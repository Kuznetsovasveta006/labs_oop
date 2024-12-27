#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "IAbility.hpp"
#include "IAbilitySettings.hpp"
#include "field.hpp"


class ScannerSettings: public AbilitySettings {
public:
    ScannerSettings(GameField& field, int x, int y, int& result);

    AbilityStatus getAbilityStatus() override;

    void acceptVisitor(Visitor& visitor) override;

    GameField field;
    int x_coord;
    int y_coord;
    int result;
};

class Scanner: public Ability {
public:
    Scanner(GameField& field, int x, int y, int& result);
    void cast() override;

private:
    GameField field;
    int x_coord;
    int y_coord;
    int result;
};

#endif //SCANNER_HPP