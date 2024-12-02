#include "AbilityManager.h"

AbilityManager::AbilityManager(){
	std::vector<AbilityNum> start_vector{AbilityNum::DoubleAttack, AbilityNum::Shelling, AbilityNum::Scaner};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(start_vector.begin(), start_vector.end(), g);

    for (const auto& ability : start_vector) {
        queue_ability.push(ability);
    }
}

AbilityManager::AbilityManager(std::queue<AbilityNum>& abilities):
    queue_ability(abilities){}

std::queue<AbilityManager::AbilityNum> AbilityManager::getQueue(){
    return queue_ability;
}

void AbilityManager::useAbility(IArguments& args){
    if (queue_ability.size() == 0) {
        throw EmptyAbilityQueueExeption("You have no ability");
    }
    Factory* factory = new Factory();
    Visitor* visitor = new Visitor(factory);
    args.accept(*visitor);
    IAbility& ability = factory->getAbility();
    ability.applyAbility();
    queue_ability.pop();
}

void AbilityManager::recieveAbility(){
    std::vector<AbilityNum> start_vector{ AbilityNum::DoubleAttack, AbilityNum::Shelling, AbilityNum::Scaner };

    int random_num = rand() % 3;
    queue_ability.push(start_vector[random_num]);
}

AbilityManager::AbilityNum AbilityManager::getInfoCurrentAbility(){
    return queue_ability.front(); 
}