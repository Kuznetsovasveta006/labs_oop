#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <stdexcept>


enum class ShipState { intact, damaged, destroyed };

class Ship {
public:
    Ship(int length);

    Ship(const Ship& other);

    Ship(Ship&& other) noexcept;

    ~Ship();
   
    int getLength() const noexcept;

    int getTopX() const noexcept;

    int getTopY() const noexcept;

    bool isHorizontal() const noexcept;

    bool isDestroyed() const noexcept;

    void addShip(int x, int y, bool new_horizontal);

    void damageSegment(int index); 
   
    ShipState getSegmentState(int index) const;  

private:   
    int length;   
    std::vector<ShipState> segments;
    int top_x;
    int top_y;
    bool horizontal;
};


#endif // SHIP_HPP