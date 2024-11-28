#include "ShipManager.h"
#include "GameField.h"
#include "AbilityManager.h"
#include "Game.h"

int main() {
    GameField field(8, 8);
    std::vector<int> my_vector = { 2, 3, 1 };
    ShipManager manager(my_vector);
    std::cout << "Free ships: " << manager.getFreeShipCount() << "\n";
    Ship& ship_1 = manager.getShip(2);
    field.addShip(ship_1, { 0,0 }, Ship::Horizontal);
    std::cout << "Free ships: " << manager.getFreeShipCount() << "\n";

    Ship& ship_2 = manager.getShip(1);
    try {
        field.addShip(ship_2, { -1,4 }, Ship::Horizontal);
    } catch (const ShipPlacementExeption& e) {
        std::cout << e.what();
    }
    field.addShip(ship_2, { 3,4 }, Ship::Horizontal);
    Ship& ship_3 = manager.getShip(0);
    field.addShip(ship_3, { 0,4 }, Ship::Vertical);

    field.print_field();
    std::cout << "\n";
    field.attack({ 0,0 });
    field.print_field();
    std::cout << "Destroyed ships: " << manager.getDetroyedShipsCount() << "\n";
    std::cout << "\n";

    AbilityManager ab_manager;

    if (field.attack({ 0,0 })) {
        ab_manager.recieveAbility();
    }

    field.print_field();
    std::cout << "Destroyed ships: " << manager.getDetroyedShipsCount() << "\n";
    std::cout << "\n";

    try {
        field.attack({ -1, 10 });
    } catch (const AttackOutOfFieldExeption& e) {
        std::cout << e.what();
    }
    std::cout << "\n";    

    DoubleAttackArguments d_arg(&field); 
    ShellingArguments sh_arg(&manager); 
    ScanerArguments sc_arg({ 0,0 }, &field);

    for (int i = 0; i < 4; i++) {
        AbilityManager::AbilityNum index = ab_manager.getInfoCurrentAbility();
        switch (index)
        {
        case AbilityManager::DoubleAttack:
            std::cout << "DoubleAttack \n";
            ab_manager.useAbility(d_arg);
            field.attack({ 3,4 });
            field.print_field();
            break;
        case AbilityManager::Shelling:
            std::cout << "Shelling \n";
            ab_manager.useAbility(sh_arg);
            field.print_field();
            break;
        case AbilityManager::Scaner:
            std::cout << "Scaner \n";
            ab_manager.useAbility(sc_arg);
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
    std::vector<int> base_vector = { 4, 3, 3, 2, 2, 2, 4, 1, 4, 4 };
    Bot bot(base_vector, 10, 10);
    bot.field->print_field();
    
    return 0;
}


// убрала указатели 
// переделала атаку 
// удалила лишние функции 
// переделала постановку корабля на поле