#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(Game& game):
	current_state(){
	current_state["round_counter"] = game.getRound();
	current_state["is_player_step"] = game.isPlayerStepNow();

	current_state["player_field_width"] = game.getPlayer().field.getWidth();
	current_state["player_field_height"] = game.getPlayer().field.getHeight();
	current_state["player_field"] = saveFieldToJson(game.getPlayer().field);
	current_state["player_ship_data"] = saveShipsToJson(game.getPlayer().ship_manager);
	current_state["player_ability_manager"] = saveAbilityManagerToJson(game.getPlayer().ability_manager);
	current_state["bot_field_width"] = game.getBot().field.getWidth();

	current_state["bot_field_height"] = game.getBot().field.getHeight();
	current_state["bot_field"] = saveFieldToJson(game.getBot().field);
	current_state["bot_ship_data"] = saveShipsToJson(game.getBot().ship_manager);
}

GameState::GameState(const std::string& file_name){
	try {
		FileHandler file_handler(file_name);
		file_handler.openForRead();
		file_handler.read(current_state);
		file_handler.closeRead();
	}
	catch (const FileError& e) {
		std::cerr << "Error while loading game state: " << e.what() << std::endl;
	}
}

json GameState::saveFieldToJson(GameField& field) {
	json field_json = json::array();
	for (int y = 0; y < field.getHeight(); ++y) {
		json row = json::array();
		for (int x = 0; x < field.getWidth(); ++x) {
			row.push_back(static_cast<int>(field.getStatus(x, y)));
		}
		field_json.push_back(row);
	}
	return field_json;
}

json GameState::saveShipsToJson(ShipManager& ship_manager){ 
	json ships_data;
	for (int i = 0; i < ship_manager.getShipsNumber(); i++) {
		Ship& ship = ship_manager.getShip(i);
		json ship_data;
		ship_data["x_coord"] = ship.getTopX();
		ship_data["y_coord"] = ship.getTopY();
		ship_data["horizontal"] = int(ship.isHorizontal());
		json segments_data;
		for (int j = 0; j < ship.getLength(); j++) {
			json segment_data;
			segment_data["status"] = static_cast<int>(ship.getSegmentState(j));
			segments_data.push_back(segment_data);
		}
		ship_data["segments"] = segments_data;
		ships_data.push_back(ship_data);
	}
	return ships_data;
}

json GameState::saveAbilityManagerToJson(AbilityManager& ability_manager){
	json abilities_json = json::array();

	std::queue<AbilityStatus> ability_queue = ability_manager.getQueue();
	while (!ability_queue.empty()) {
		AbilityStatus ability = ability_queue.front();
		abilities_json.push_back(static_cast<int>(ability));
		ability_queue.pop();
	}
	return abilities_json;
}

bool GameState::save(const std::string& file_name){
	try {
		FileHandler file_handler(file_name);
		file_handler.openForWrite();
		file_handler.write(current_state);
		file_handler.closeWrite();
		return true;
	}
	catch (const FileError& e) {
		std::cerr << "Error while saving game state: " << e.what() << std::endl;
	}
	return false;
}

GameField GameState::loadFieldFromJson(int width, int height, json& field_data){
	GameField field(width, height);
	for (int y = 0; y < int(field_data.size()); ++y) {
		for (int x = 0; x < int(field_data[y].size()); ++x) {
			field.setStatus(x, y, static_cast<CellStatus>(field_data[y][x].get<int>()));
		}
	}
	return field;
}

ShipManager GameState::loadShipManagerFromJson(json& ships_data, GameField& field){
	std::vector<int> ship_sizes;
	for (const auto& ship_data : ships_data) {
		ship_sizes.push_back(ship_data["segments"].size());
	}
	ShipManager ship_manager(ship_sizes);
	for (int i = 0; i < int(ships_data.size()); ++i) {
		const auto& ship_data = ships_data[i];
		Ship& ship = ship_manager.getShip(i);
		int x = ship_data["x_coord"];
		int y = ship_data["y_coord"];
		bool horizontal = bool(ship_data["horizontal"].get<int>());
		field.placeShip(ship, x, y, horizontal);
		const auto& segments_data = ship_data["segments"];
		for (int j = 0; j < int(segments_data.size()); ++j) {
			if (segments_data[j]["status"] == 1) {
				ship.damageSegment(j);
			}
			if (segments_data[j]["status"] == 2) {
				ship.damageSegment(j);
                ship.damageSegment(j);
			}
		}
	}
	return ship_manager;
}

AbilityManager GameState::loadAbilityManagerFromJson(json& ability_data){
	std::queue<AbilityStatus> abilities; 
	for (const auto& ability : ability_data) { 
		abilities.push(static_cast<AbilityStatus>(ability.get<int>())); 
	}
	AbilityManager ability_manager(abilities);
	return ability_manager;
}

Game GameState::load(){ 
	int round = current_state["round_counter"];
	bool is_player_step = current_state["is_player_step"];

	int player_field_width = current_state["player_field_width"];
	int player_field_height = current_state["player_field_height"];

	GameField *player_field = new GameField(loadFieldFromJson(player_field_width, player_field_height, current_state["player_field"])); 
	ShipManager *player_ship_manager = new ShipManager(loadShipManagerFromJson(current_state["player_ship_data"], *player_field));
	AbilityManager *player_ability_manager = new AbilityManager(loadAbilityManagerFromJson(current_state["player_ability_manager"]));

	int bot_field_width = current_state["bot_field_width"];
	int bot_field_height = current_state["bot_field_height"];

	GameField *bot_field = new GameField(loadFieldFromJson(bot_field_width, bot_field_height, current_state["bot_field"])); 
	ShipManager *bot_ship_manager = new ShipManager(loadShipManagerFromJson(current_state["bot_ship_data"], *bot_field));

	Player* player = new Player(*player_field, *player_ship_manager, *player_ability_manager);
	Bot* bot = new Bot(*bot_field, *bot_ship_manager);

	return Game(player, bot, round, is_player_step);
}

std::ostream& operator<<(std::ostream& os, GameState& state){
	os << state.current_state.dump(4) << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, GameState& state){
	json input_data;
	is >> input_data;
	state.current_state = input_data;
	return is;
}