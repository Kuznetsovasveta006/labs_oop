#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>   
#include <vector>   
#include <stdexcept>   

#include "ship.hpp"

enum class CellStatus { unknown, empty, ship };

class GameField { 
public:
    GameField(int width, int height);

    GameField(const GameField& other);

    GameField(GameField&& other);

    GameField& operator=(const GameField& other);

    GameField& operator=(GameField&& other);

    ~GameField();

    bool checkCoords(int x, int y);

    bool hasShip(int x, int y);

    ShipState getShipSegmentStatus(int x, int y) const;

    CellStatus getStatus(int x, int y) const;

    void setStatus(int x, int y, CellStatus new_status);
   
    void placeShip(Ship& ship, int x, int y, bool horizontal);

    void setDoubleAttack();

    int getWidth();

    int getHeight();

    bool attack(int x, int y);

private:   
    class FieldCell{
    public:

        FieldCell();

        ~FieldCell();

        CellStatus getStatus() const noexcept;

        void setShip(Ship& new_ship, int new_index) noexcept;

        void setStatus(CellStatus new_status) noexcept;

        bool isShip() const noexcept;

        bool attackCell() noexcept;

        ShipState getShipSegmentStatus() const noexcept;

    private:
        CellStatus status; //статус клетки
        Ship* ship;
        int index; //индекс сегмента корабля
    };

    int width;   
    int height;
    bool double_damage;
    std::vector<std::vector<FieldCell>> field; // Поле   
};


#endif //FIELD_HPP