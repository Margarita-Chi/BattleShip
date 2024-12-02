#pragma once

#include <queue>
#include "Visitor.h"
#include <algorithm>
#include <random> 
#include "EmptyAbilityQueueExeption.h"

class AbilityManager{
public:
	enum AbilityNum {
		DoubleAttack,
		Shelling,
		Scaner
	};

	AbilityManager();

	~AbilityManager() = default;

	AbilityManager(std::queue<AbilityNum>& abilities);

	std::queue<AbilityNum> getQueue();

	void useAbility(IArguments& args);

	void recieveAbility();

	AbilityNum getInfoCurrentAbility();

private:
	std::queue<AbilityNum> queue_ability;

};

