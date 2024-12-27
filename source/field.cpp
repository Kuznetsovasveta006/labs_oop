#include "field.hpp"
#include "ShipCollisionError.hpp"
#include "AttackCoordinatesError.hpp"


GameField::FieldCell::FieldCell() {
    status = CellStatus::unknown;
    ship = nullptr;
    index = -1;
}

GameField::FieldCell::~FieldCell() = default;

GameField::GameField(int width, int height)   
    : width(width), height(height) {   
    if (width <= 0 or height <= 0) {   
        throw std::invalid_argument("Field dimensions must be positive");   
    }   

    field.resize(width);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            field[i].push_back(FieldCell());
        }
    }   
}

GameField::GameField(const GameField& other)
    : width(other.width), 
    height(other.height),
    field(other.field)
{}

GameField::GameField(GameField&& other) :
    width(std::move(other.width)),
    height(std::move(other.height)),
    field(std::move(other.field))
{}

GameField& GameField::operator=(const GameField& other) {
    if (this == &other) {
        return *this;
    }

    width = other.width;
    height = other.height;
    field = other.field;

    return *this;
}

GameField& GameField::operator=(GameField&& other) {
    if (this == &other) {
        return *this;
    }

    width = std::move(other.width);
    height = std::move(other.height);
    field = std::move(other.field);

    return *this;
}

GameField::~GameField() {
    for (int j = 0; j < height; ++j) {
        field[j].clear();
    }

    field.clear();
}

bool GameField::checkCoords(int x, int y) {
    return x >= 0 and x < width and y >= 0 and y < height;
}

bool GameField::hasShip(int x, int y) {
    return field[y][x].isShip();
}

ShipState GameField::getShipSegmentStatus(int x, int y) const
{
    if (x < 0 or x >= width or y < 0 or y >= height) {   
        throw std::out_of_range("Wrong coordinates"); 
    }   
    return field[y][x].getShipSegmentStatus();
}

CellStatus GameField::getStatus(int x, int y) const
{
    if (x < 0 or x >= width or y < 0 or y >= height) {   
        throw std::out_of_range("Wrong coordinates"); 
    }   
    return field[y][x].getStatus();
}

void GameField::setStatus(int x, int y, CellStatus new_status)
{
    if (x < 0 or x >= width or y < 0 or y >= height) {   
        throw std::out_of_range("Wrong coordinates"); 
    }   
    field[y][x].setStatus(new_status);
}

void GameField::placeShip(Ship& ship, int x, int y, bool horizontal) {
    int x_offset, y_offset;
    if (horizontal) { 
        x_offset = ship.getLength()-1; 
        y_offset = 0; 
    } 
    else { 
        x_offset = 0; 
        y_offset = ship.getLength()-1; 
    } 

    if (x + x_offset >= width or y + y_offset >= height) {   
        throw ShipCollisionError(x, y);   
    }
    for (int j = std::max(0,y-1); j <= std::min(height-1, y+y_offset+1); ++j) { 
        for (int i = std::max(0,x-1); i <= std::min(width-1, x+x_offset+1); ++i) { 
            if (field[j][i].isShip()) { 
                throw ShipCollisionError(i, j);
            } 
        } 
    } 
        
    int index=0;
    for(int j = y; j <= y+y_offset; j++){
        for (int i = x; i <= x+x_offset; ++i) { 
            field[j][i].setShip(ship, index++); // Помещаем корабль на поле   
        }  
    }
    ship.addShip(x, y, horizontal);
}

void GameField::setDoubleAttack() {
	double_damage = true;
}

int GameField::getWidth() {
    return width;
}

int GameField::getHeight() {
    return height;
}

bool GameField::attack(int x, int y) {
    bool destroy_flag = false;
    if (x < 0 or x >= width or y < 0 or y >= height) {   
        throw AttackCoordinatesError(x, y);   
    }   
    if (field[y][x].isShip()) {
        destroy_flag = field[y][x].attackCell();
        if (double_damage) {
			destroy_flag = field[y][x].attackCell();
			double_damage = false;
        }
        field[y][x].setStatus(CellStatus::ship);
    }
    else {
        field[y][x].setStatus(CellStatus::empty);
    }
    return destroy_flag;
} 


CellStatus GameField::FieldCell::getStatus() const noexcept { return status; }

void GameField::FieldCell::setShip(Ship& new_ship, int new_index) noexcept { 
    ship = &new_ship;
    index = new_index;
}

void GameField::FieldCell::setStatus(CellStatus new_status) noexcept { status = new_status; }

bool GameField::FieldCell::isShip() const noexcept { return ship != nullptr; }

bool GameField::FieldCell::attackCell() noexcept { 
    ship->damageSegment(index); 
    if (ship->isDestroyed()) {
        return true;
    }
    return false;
}

ShipState GameField::FieldCell::getShipSegmentStatus() const noexcept { return ship->getSegmentState(index); }