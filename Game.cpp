#include "Game.h"

Game::Game(Player* player):
	round(0),
	is_player_step(true),
	player(player){
	bot = new Bot(player->ship_manager->getShipSizes(), player->field->getWidth(), player->field->getHeight());
}

Game::Game(Player* player, Bot* bot, int round, bool player_step):
	player(player),
	bot(bot),
	round(round),
	is_player_step(player_step){}

Game::Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships) :
	round(0),
	is_player_step(true),
	player(player) {
	bot = new Bot(size_bot_ships,width_bot, height_bot);
}

Game::~Game(){
	if (player) {
		delete player;
	}
	if (bot) {
		delete bot;
	}
}

void Game::player_step(Coords coords){
	try {
		bot->field->attack(coords);
	} catch (const AttackOutOfFieldExeption& e) {
		throw;
	}
}

bool Game::botAttack(){
	bool is_right_coords = false;
	int x;
	int y;
	while (!is_right_coords) {
		x = rand() % player->field->getWidth();
		y = rand() % player->field->getHeight();
		is_right_coords = true;
		if (player->field->isShipHereDestroyed({ x, y }) ||
			player->field->getCellStatus({x,y}) == Cell::empty) {
			is_right_coords = false;
		}
	}
	if (player->ship_manager->getAliveShips() == std::vector<Ship*>{}) {
		return true;
	}
	return false;
}

bool Game::is_player_step_now(){
	return is_player_step;
}

Player& Game::getPlayer(){
	return *(player);
}

Bot& Game::getBot(){
	return *(bot);
}

void Game::newRound(){
	round += 1;
	std::vector<int> bot_ships = bot->ship_manager->getShipSizes();
	int width = bot->field->getWidth();
	int height = bot->field->getHeight();
	delete bot;
	bot = new Bot(bot_ships, width, height);
}

