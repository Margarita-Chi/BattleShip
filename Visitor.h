#pragma once

#include "Factory.h"

class Visitor : public IVisitor {
public:
	Visitor(Factory* factory);

	void Visit(DoubleAttackArguments& args);

	void Visit(ScanerArguments& args);

	void Visit(ShellingArguments& args);

private:
	Factory* factory = nullptr;
};