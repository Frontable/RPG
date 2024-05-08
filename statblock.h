#pragma once
#include <cstdint>

typedef std::uint16_t stattype;

class StatBlock
{

	stattype Strenght;
	stattype Intellect;

public:

	StatBlock()
	{
		Strenght = (stattype)1u;
		Intellect = (stattype)1u;
	}

	explicit StatBlock(stattype s, stattype i)
	{
		Strenght = s;
		Intellect = i;
	}

	stattype getStrenght() { return Strenght; }

	stattype getIntellect() { return Intellect; }

protected:

	void increaseStats(stattype s, stattype i)
	{
		Strenght += s;
		Intellect += i;
	}

};