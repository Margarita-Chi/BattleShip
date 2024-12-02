#pragma once

#include "IVisitor.h"

struct IArguments {
	virtual void accept(IVisitor& visitor) = 0;
};