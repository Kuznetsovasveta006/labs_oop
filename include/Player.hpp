#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "field.hpp"
#include "shipmanager.hpp"
#include "AbilityManager.hpp"

struct Player{
	GameField field;
	ShipManager ship_manager;
	AbilityManager ability_manager;

	Player(GameField& field, ShipManager& ship_manager, AbilityManager& ability_manager)
		: field(field), ship_manager(ship_manager), ability_manager(ability_manager) {}
	
	~Player() = default;
};

#endif //  PLAYER_HPP