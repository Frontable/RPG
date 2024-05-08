#pragma once
#include <string>
#include "statblock.h"

struct  Buff
{
	Buff(std::string name = "unnamed", uint16_t dur = 2u, stattype str = 0u, stattype agi = 0u, stattype intel = 0u,
		stattype arm = 0u, stattype elres = 0u, bool isdebuff = false)
		:Name(name), Durotation(dur), Strength(str), Agility(agi), Intellect(intel),
		Armor(arm), ElementRes(elres), isDebuff(isdebuff)
	{

	}

	std::string Name;
	uint16_t Durotation;
	stattype Strength;
	stattype Agility;
	stattype Intellect;
	stattype Armor;
	stattype ElementRes;
	bool isDebuff;

};