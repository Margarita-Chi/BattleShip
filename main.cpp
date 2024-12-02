#include "ShipManager.h"
#include "GameField.h"
#include "AbilityManager.h"
#include "Gamestate.h"

int main() {
    GameField field(8, 8);
    std::vector<int> my_vector = { 2, 3, 1 };
    ShipManager manager(my_vector);
    Ship& ship_1 = manager.getShip(2);
    field.addShip(ship_1, { 0,0 }, Ship::Horizontal);
    Ship& ship_2 = manager.getShip(1);
    field.addShip(ship_2, { 3,4 }, Ship::Horizontal);
    Ship& ship_3 = manager.getShip(0);
    field.addShip(ship_3, { 0,4 }, Ship::Vertical);
    AbilityManager ab_manager;

    field.print_field();
    std::cout << "\n";

    Player player(field, manager, ab_manager, false);
    Game game(&player);
    GameState game_state(game);
    game_state.save("game_state.json");

    
    game.playerAttack({ 0,0 });
    game.playerAttack({ 3,3 });

    std::cout << "bot1\n";
    game.getBot().field.print_field_ver_ox();
    std::cout << "\n";

    GameState new_game_state("game_state.json");
    Game new_game = new_game_state.load();

    std::cout << "bot2\n";
    new_game.getBot().field.print_field_ver_ox();
    std::cout << "\n";

    
    std::cout << "bot\n";
    new_game.getBot().field.print_field_ver_ox();
    std::cout << "\n";
    std::cout << "player\n";
    new_game.getPlayer().field.print_field_ver_ox();
    std::cout << "\n";

    DoubleAttackArguments d_arg(&field); 
    ShellingArguments sh_arg(&manager); 
    ScanerArguments sc_arg({ 0,0 }, &field);

    for (int i = 0; i < 3; i++) {
        AbilityManager::AbilityNum index = game.getPlayer().ability_manager.getInfoCurrentAbility();
        switch (index)
        {
        case AbilityManager::DoubleAttack:
            std::cout << "DoubleAttack \n";
            game.playerUseAbility(d_arg);
            game.getBot().field.print_field();
            break;
        case AbilityManager::Shelling:
            std::cout << "Shelling \n";
            game.playerUseAbility(sh_arg);
            game.getBot().field.print_field();
            break;
        case AbilityManager::Scaner:
            std::cout << "Scaner \n";
            game.playerUseAbility(sc_arg);
            break;
        default:
            break;
        }
    }
    try {
        ab_manager.useAbility(d_arg);
        field.attack({ 3,4 });
        field.print_field();
    }
    catch (const EmptyAbilityQueueExeption& e) {
        std::cout << e.what();
    }
    return 0;
}