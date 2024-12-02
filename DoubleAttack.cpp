#include "DoubleAttack.h"

DoubleAttack::DoubleAttack(GameField* field) :
	field(field) {}

void DoubleAttack::applyAbility(){
	field->setDoubleAttack();
};