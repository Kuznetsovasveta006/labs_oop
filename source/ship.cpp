#include "ship.hpp"
#include "DamageError.hpp"


Ship::Ship(int length)   
    : length(length), segments(length, ShipState::intact), top_x(-1), top_y(-1), horizontal(0) { 
    if (length < 1 or length > 4) {   
        throw std::invalid_argument("Ship length must be between 1 and 4");   
    }   
}

Ship::Ship(const Ship& other)
	: length(other.length),
    segments(other.segments),
	top_x(other.top_x),
	top_y(other.top_y),
	horizontal(other.horizontal)
{}

Ship::Ship(Ship&& other) noexcept
	: length(other.length),
	segments(std::move(other.segments)),
	top_x(other.top_x),
	top_y(other.top_y),
	horizontal(other.horizontal)
{}

Ship::~Ship() = default;

int Ship::getLength() const noexcept { return length; } 

int Ship::getTopX() const noexcept { return top_x; }

int Ship::getTopY() const noexcept { return top_y; }

bool Ship::isHorizontal() const noexcept { return horizontal; }

bool Ship::isDestroyed() const noexcept {   
    for (const auto& state : segments) {
        if (state != ShipState::destroyed) return false;   
    }   
    return true;   
}

void Ship::addShip(int x, int y, bool new_horizontal) {
	horizontal = new_horizontal;
	top_x = x;
    top_y = y;
}
   
void Ship::damageSegment(int index) {   
    if (index < 0 or index >= length) {   
        throw std::out_of_range("Segment index out of range");   
    }
    
    if (segments[index] == ShipState::intact) {   
            segments[index] = ShipState::damaged;
    }
    else {
            segments[index] = ShipState::destroyed;   
    }
   
}   
   
ShipState Ship::getSegmentState(int index) const {   
    if (index < 0 or index >= length) {   
        throw std::out_of_range("Segment index out of range");   
    }   
    return segments[index];   
}    
