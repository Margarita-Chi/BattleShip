#include "Factory.h"

IAbility& Factory::getAbility(){
    return *current_ability;
}

void Factory::buildScaner(ScanerArguments& scaner_args){
    current_ability = new Scaner(scaner_args.coords, scaner_args.field);
}

void Factory::buildDoubleAttack(DoubleAttackArguments& double_attack_args){
    current_ability = new DoubleAttack(double_attack_args.field);
}

void Factory::buildShelling(ShellingArguments& shelling_args){
    current_ability = new Shelling(shelling_args.ship_manager);
}


