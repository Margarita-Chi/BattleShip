#include "Player.h"
#include "Bot.h"

class Game {
public:
    Game(Player* player);

    Game(Player* player, Bot* bot, int round, bool player_step, bool is_player_use_ability, bool is_player_do_attack);

    Game(Player* player, int width_bot, int height_bot, std::vector<int> size_bot_ships);

    ~Game();

    void playerAttack(Coords coords);

    void playerUseAbility(IArguments& args);

    bool botAttack(); // true, если бот выиграл

    bool isPlayerStepNow();

    bool isPlayerUseAbility();

    bool isPlayerDoAttack();

    int getRound();

    Player& getPlayer();

    Bot& getBot();

private:
    void newRound();

    void checkFlags(bool& is_player_use_ability, bool& is_player_do_attack, bool& is_player_step);

    Player* player;
    Bot* bot;
    bool is_player_use_ability;
    bool is_player_do_attack;
    bool is_player_step;
    int round;
};
