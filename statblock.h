#pragma once
#include <cstdint>

typedef std::uint16_t stattype;

class StatBlock
{

	stattype Strength;
	stattype Agility;
	stattype Intellect;
	stattype Armor;
	stattype ElementRes;

public:
	explicit StatBlock(stattype s = 1, stattype a = 1, stattype i = 1, stattype arm = 0, stattype elres = 0) {
		Strength = s;
		Agility = a;
		Intellect = i;
		Armor = arm;
		ElementRes = elres;
	}

	stattype getStrength() { return Strength; }
	stattype getAgility() { return Agility; }
	stattype getIntellect() { return Intellect; }	
	stattype getArmor() { return Armor; }
	stattype getElementRes() { return ElementRes; }

protected:

	void increaseStats(stattype s = 0, stattype a = 0, stattype i = 0, stattype arm = 0, stattype elres = 0) {
		Strength += s;
		Agility += a;
		Intellect += i;
		Armor += arm;
		ElementRes += elres;
	}

};