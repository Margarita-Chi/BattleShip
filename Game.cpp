#include "Game.h"

Game::Game(Player* player) :
    round(0),
    is_player_step(true),
    player(player),
    is_player_do_attack(false),
    is_player_use_ability(false) {
    bot = new Bot(player->ship_manager.getShipSizes(), player->field.getWidth(), player->field.getHeight());
}
Game::Game(Player* player, Bot* bot, int round, bool player_step, bool is_player_use_ability, bool is_player_do_attack) :
    player(player),
    bot(bot),
    round(round),
    is_player_step(player_step),
    is_player_do_attack(is_player_do_attack),
    is_player_use_ability(is_player_use_ability) {}

Game::Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships) :
    round(0),
    is_player_step(true),
    player(player),
    is_player_do_attack(false),
    is_player_use_ability(false) {
    bot = new Bot(size_bot_ships, width_bot, height_bot);
}

Game::~Game() {
    //delete player;
    delete bot;
}

void Game::playerAttack(Coords coords) {
    bool flag;
    try {
        flag = bot->field.attack(coords);
    }
    catch (const AttackOutOfFieldExeption& e) {
        std::cout << e.what();
    }
    if (flag) {
        player->ability_manager.recieveAbility();
    }
    is_player_do_attack = true;
    checkFlags(is_player_use_ability, is_player_do_attack, is_player_step);
}

void Game::playerUseAbility(IArguments& args) {
    try {
        player->ability_manager.useAbility(args);
    }
    catch (const EmptyAbilityQueueExeption& e) {
        std::cout << e.what();
    }
    is_player_use_ability = true;
    checkFlags(is_player_use_ability, is_player_do_attack, is_player_step);
}

bool Game::botAttack() {
    bool is_right_coords = false;
    int x;
    int y;
    while (!is_right_coords) {
        x = rand() % player->field.getWidth();
        y = rand() % player->field.getHeight();
        is_right_coords = true;
        if (player->field.isShipHereDestroyed({ x, y }) ||
            player->field.getCellStatus({ x,y }) == Cell::empty) {
            is_right_coords = false;
        }
    }
    player->field.attack({ x,y });
    is_player_do_attack = false;
    is_player_use_ability = false;
    is_player_step = true;
    if (player->ship_manager.getAliveShips() == std::vector<Ship*>{}) {
        return true;
    }
    return false;
}

bool Game::isPlayerStepNow() {
    return is_player_step;
}

bool Game::isPlayerUseAbility() {
    return is_player_use_ability;
}

bool Game::isPlayerDoAttack() {
    return is_player_do_attack;
}

int Game::getRound() {
    return round;
}

Player& Game::getPlayer() {
    return *player;
}

Bot& Game::getBot() {
    return *bot;
}

void Game::newRound() {
    round += 1;
    std::vector<int> bot_ships = bot->ship_manager.getShipSizes();
    int width = bot->field.getWidth();
    int height = bot->field.getHeight();
    delete bot;
    bot = new Bot(bot_ships, width, height);
}

void Game::checkFlags(bool& is_player_use_ability, bool& is_player_do_attack, bool& is_player_step) {
    if (is_player_use_ability && is_player_do_attack) {
        is_player_step = false;
    }
}
