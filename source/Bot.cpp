#include "Bot.hpp"


Bot::Bot() 
	: field(10, 10), ship_manager({1, 1, 1, 1, 2, 2, 2, 3, 3, 4}) {
	shipGenerate(ship_manager);
}

Bot::Bot(std::vector<int> ship_sizes, int width, int height) 
	: field(width, height), ship_manager(ship_sizes) {
	shipGenerate(ship_manager);
}

Bot::Bot(const Bot& other)
    : field(other.field), ship_manager(other.ship_manager) 
{}

Bot::Bot(Bot&& other) noexcept
	: field(std::move(other.field)), ship_manager(std::move(other.ship_manager)) 
{}

Bot::Bot(GameField& field, ShipManager& ship_manager)
	: field(field), ship_manager(ship_manager)
{}

void Bot::shipGenerate(ShipManager& ship_manager) {
	int ship_manager_size = ship_manager.getShipsNumber();
	for (int i = 0; i < ship_manager_size; i++) {
		Ship& ship = ship_manager.getShip(i);
		bool flag = true;
		while (flag) {
			try {
				int width = rand() % field.getWidth();
				int height = rand() % field.getHeight();
				bool orientation = bool(rand() % 2);
				field.placeShip(ship, width, height, orientation);
				flag = false;
			} catch (const ShipCollisionError& e) {
				flag = true;
			}
		}
	}
}