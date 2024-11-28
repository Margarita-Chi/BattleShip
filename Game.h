#pragma once
#include "Player.h"
#include "Bot.h"

class Game {
public:
	Game(Player* player);

	Game(Player* player, Bot* bot, int round, bool player_step);

	Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships);

	~Game();

	void player_step(Coords coords); // ???

	void player_step(Coords coords, IArguments& args); // ???
	
	bool botAttack(); // true, если бот выиграл

	bool is_player_step_now();

	Player& getPlayer();

	Bot& getBot();

private:
	void newRound();

	Player* player;
	Bot* bot;
	bool is_player_step;
	int round;
};