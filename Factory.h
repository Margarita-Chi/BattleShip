#pragma once

#include "ScanerArguments.h"
#include "DoubleAttackArguments.h"
#include "ShellingArguments.h"
#include "Scaner.h"
#include "Shelling.h"
#include "DoubleAttack.h"

class Factory
{
public:
	IAbility& getAbility();

	void buildScaner(ScanerArguments& scaner_args);

	void buildDoubleAttack(DoubleAttackArguments& double_attack_args);

	void buildShelling(ShellingArguments& shelling_args);

private:
	IAbility* current_ability = nullptr;
};