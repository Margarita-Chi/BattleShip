#include "ShipManager.h"

int main() {
    GameField field(8, 8);
    std::vector<int> my_vector = { 2, 3, 1 };
    ShipManager manager(my_vector);
    std::cout << "Free ships: " << manager.getFreeShipCount() << "\n";
    manager.addShipToField(field, 2, { 0,0 }, Ship::Horizontal);
    std::cout << "Free ships: " << manager.getFreeShipCount() << "\n";
    std::cout << "Active ships: " << manager.getFreeShipCount() << "\n";
    manager.addShipToField(field, 2, { 0,0 }, Ship::Horizontal); //ничего не происходит если индекс неправильный
    manager.addShipToField(field, 1, { 3,4 }, Ship::Horizontal);
    manager.addShipToField(field, 0, { 0,4 }, Ship::Vertical);
    field.print_field();
    std::cout << "\n";
    field.attack({ 0,0 });
    field.print_field();
    std::cout << "Destroyed ships: " << manager.getDetroyedShipsCount() << "\n";
    std::cout << "Alive ships: " << manager.getAliveShipsCount() << "\n";
    std::cout << "\n";
    field.attack({ 0,0 });
    field.print_field();
    std::cout << "Destroyed ships: " << manager.getDetroyedShipsCount() << "\n";
    std::cout << "Alive ships: " << manager.getAliveShipsCount() << "\n";
    std::cout << "\n";
    return 0;
}