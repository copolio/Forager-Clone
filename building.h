#pragma once
#include "unit.h"
enum class builType {
	STEELWORK,
	ANVIL,
};
class building : public unit
{
private:
	builType builId;
	RECT interactionRc;
};

