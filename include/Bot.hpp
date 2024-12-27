#ifndef BOT_HPP
#define BOT_HPP

#include "shipmanager.hpp"
#include "field.hpp"
#include "ShipCollisionError.hpp"

#include <vector>
#include <algorithm>
#include <random>


class Bot {
public:
	Bot();

	Bot(std::vector<int> ship_sizes, int width, int height);

	Bot(const Bot& other);

	Bot(Bot&& other) noexcept;

	Bot(GameField& field, ShipManager& ship_manager);

	~Bot() = default;

	void shipGenerate(ShipManager& ship_manager);

	GameField field;
	ShipManager ship_manager;
};

#endif // BOT_HPP