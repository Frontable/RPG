#pragma once
#include <cstdint>
#include <string>

enum class ABILITYTARGET { SELF, ALLY, ENEMY };
enum class ABILITYSCALAR { NONE, STR, AGI, INT};

struct Ability
{
	Ability(std::string name, uint32_t cost, uint32_t cd, ABILITYTARGET t, uint32_t hpe, ABILITYSCALAR s)
		:Name(name), Cost(cost), Cooldown(cd), Target(t), HpEffect(hpe), Scalar(s)
	{

	}

	std::string Name = "unnamed";
	uint32_t Cost = 0; //mp if there is a cost
	uint32_t Cooldown = 1; // rounds cooldown
	ABILITYTARGET Target = ABILITYTARGET::SELF;
	uint32_t HpEffect = 1;
	ABILITYSCALAR Scalar = ABILITYSCALAR::NONE;

};