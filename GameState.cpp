#include "GameState.h"

GameState::GameState(Game& game):
	current_state(){
	current_state["round_counter"] = game.getRound();
	current_state["is_player_step"] = game.isPlayerStepNow();
	current_state["is_player_use_ability"] = game.isPlayerUseAbility();
	current_state["is_player_do_attack"] = game.isPlayerDoAttack();

	current_state["player_double_attack"] = game.getPlayer().double_attack;
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
	catch (const FileExeption& e) {
		std::cerr << "Error while loading game state: " << e.what() << std::endl;
	}
}

json GameState::saveFieldToJson(GameField& field) {
	json field_json = json::array();
	for (int y = 0; y < field.getHeight(); ++y) {
		json row = json::array();
		for (int x = 0; x < field.getWidth(); ++x) {
			row.push_back(static_cast<int>(field.getCellStatus({ x,y })));
		}
		field_json.push_back(row);
	}
	return field_json;
}

json GameState::saveShipsToJson(ShipManager& ship_manager){ 
	json ships_data;
	for (int i = 0; i < ship_manager.getShipCount(); i++) {
		Ship& ship = ship_manager.getShip(i);
		json ship_data;
		ship_data["coords"] = { ship.getCoords().x, ship.getCoords().y };
		ship_data["orientation"] = static_cast<int>(ship.getOrientation());
		json segments_data;
		for (int j = 0; j < ship.getSize(); j++) {
			Ship::ShipSegment& segment = ship.getSegmentByIndex(j);
			json segment_data;
			segment_data["status"] = static_cast<int>(segment.getStatus());
			segments_data.push_back(segment_data);
		}
		ship_data["segments"] = segments_data;
		ships_data.push_back(ship_data);
	}
	return ships_data;
}

json GameState::saveAbilityManagerToJson(AbilityManager& ability_manager){
	json abilities_json = json::array();

	std::queue<AbilityManager::AbilityNum> temp_queue = ability_manager.getQueue();
	while (!temp_queue.empty()) {
		AbilityManager::AbilityNum ability = temp_queue.front();
		abilities_json.push_back(static_cast<int>(ability));
		temp_queue.pop();
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
	catch (const FileExeption& e) {
		std::cerr << "Error while saving game state: " << e.what() << std::endl;
	}
	return false;
}

GameField GameState::loadFieldFromJson(int width, int height, json& field_data){
	GameField field(width, height);
	for (int y = 0; y < field_data.size(); ++y) {
		for (int x = 0; x < field_data[y].size(); ++x) {
			field.setCellStatus({x, y}, static_cast<Cell::status>(field_data[y][x].get<int>()));
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
	for (int i = 0; i < ships_data.size(); ++i) {
		const auto& ship_data = ships_data[i];
		Ship& ship = ship_manager.getShip(i);
		Coords coords = {ship_data["coords"][0], ship_data["coords"][1]};
		Ship::Orientation orientation = static_cast<Ship::Orientation>(ship_data["orientation"].get<int>());
		field.addShip(ship, coords, orientation);
		const auto& segments_data = ship_data["segments"];
		for (size_t j = 0; j < segments_data.size(); ++j) {
			Ship::ShipSegment& segment = ship.getSegmentByIndex(j);
			if (segments_data[j]["status"] == 1) {
				segment.attack();
			}
			if (segments_data[j]["status"] == 2) {
				segment.attack();
				segment.attack();
			}
		}
	}
	return ship_manager;
}

AbilityManager GameState::loadAbilityManagerFromJson(json& ability_data){
	std::queue<AbilityManager::AbilityNum> abilities; 
	for (const auto& ability : ability_data) { 
		abilities.push(static_cast<AbilityManager::AbilityNum>(ability.get<int>())); 
	}
	AbilityManager ability_manager(abilities);
	return ability_manager;
}

Game GameState::load(){
	int round = current_state["round_counter"];
	bool is_player_step = current_state["is_player_step"];
	bool is_player_use_ability = current_state["is_player_use_ability"];
	bool is_player_do_attack = current_state["is_player_do_attack"];
	
	bool double_attack = current_state["player_double_attack"];
	int player_field_width = current_state["player_field_width"];
	int player_field_height = current_state["player_field_height"];
	GameField player_field = loadFieldFromJson(player_field_width, player_field_height, current_state["player_field"]);
	ShipManager player_ship_manager = loadShipManagerFromJson(current_state["player_ship_data"], player_field);
	AbilityManager player_ability_manager = loadAbilityManagerFromJson(current_state["player_ability_manager"]);
	
	int bot_field_width = current_state["bot_field_width"];
	int bot_field_height = current_state["bot_field_height"];
	GameField bot_field = loadFieldFromJson(bot_field_width, bot_field_height, current_state["bot_field"]);
	ShipManager bot_ship_manager = loadShipManagerFromJson(current_state["bot_ship_data"], bot_field);

	Player* player = new Player(player_field, player_ship_manager, player_ability_manager, false);
	Bot* bot = new Bot(bot_ship_manager, bot_field);

	return Game(player, bot, round, is_player_step, is_player_use_ability, is_player_do_attack);
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