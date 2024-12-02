#include "Visitor.h"

Visitor::Visitor(Factory* factory) :
	factory(factory) {}

void Visitor::Visit(DoubleAttackArguments& args){
	factory->buildDoubleAttack(args);
}

void Visitor::Visit(ScanerArguments& args){
	factory->buildScaner(args);
}

void Visitor::Visit(ShellingArguments& args){
	factory->buildShelling(args);
};