#pragma once
#include <cstdint>
#include "pointwell.h"
#include "statblock.h"
#include <memory>
#include <string>

typedef std::uint16_t leveltype;
typedef std::uint64_t exptype;

class PlayerCharacterDelegate : public StatBlock
{

public:
	
	static const exptype LEVEL2AT = 100u;

	PlayerCharacterDelegate() : StatBlock(0u, 0u)
	{
		CurrentLevel = 1u;
		CurrentEXP = 0u;
		EXPToNextLevel = LEVEL2AT;
		HP = std::make_unique<PointWell>();
	}

	void gainEXP(exptype gainedEXP)
	{
		CurrentEXP += gainedEXP;
		while (checkIfLeveled()) {};
	}

	leveltype getLevel() { return CurrentLevel; }

	exptype getCurrentEXP() { return CurrentEXP; }

	exptype getEXPToNextLevel() { return EXPToNextLevel; }

	virtual void LevelUp() = 0;

	virtual std::string getClassName() = 0;

	std::unique_ptr<PointWell> HP;

protected:
	leveltype CurrentLevel;
	exptype CurrentEXP;
	exptype EXPToNextLevel;

	bool checkIfLeveled() {
		static const leveltype LEVELSCALAR = 2u;
		if (CurrentEXP >= EXPToNextLevel)
		{
			CurrentLevel++;
			LevelUp();
			EXPToNextLevel *= LEVELSCALAR;
			return true;
		}
		return false;
	}
	
};

#define PCCONSTRUCT : PlayerCharacterDelegate()\
{\
	HP->setMax(BASEHP);\
	HP->increaseCurrent(BASEHP);\
	increaseStats(BASEINT, BASEINT);\
}

#define CHARACTERCLASS(classname, basehp, basestr, baseint, baseagi) \
class classname : public PlayerCharacterDelegate {\
public:\
	static const welltype BASEHP = (welltype)basehp;\
	static const stattype BASESTR = (stattype)basestr;\
	static const stattype BASEINT = (stattype)baseint;\
	static const stattype BASEAGI = (stattype)baseagi;\
	std::string getClassName() override { return std::string(#classname); }\
	classname() PCCONSTRUCT \
private:\
	LEVELUP \
};

#define LEVELUP void LevelUp() override {\
HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax()));\
HP->increaseCurrent((welltype)(BASEHP / 2.f));\
increaseStats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f));\
}

CHARACTERCLASS(Warrior, 14, 3, 5, 1)
CHARACTERCLASS(Paladin, 10, 1, 8, 1)
CHARACTERCLASS(Rogue, 18, 5, 2, 2)
CHARACTERCLASS(Wizard, 12, 3, 3, 5)
CHARACTERCLASS(Cleric, 12, 3, 3, 5)
 
class PlayerCharacter
{
private:

	PlayerCharacterDelegate* pcclass;

public:

	PlayerCharacter() = delete;
	PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc){	}
	~PlayerCharacter() { delete pcclass; pcclass = nullptr; }

	std::string getClassName() { return pcclass->getClassName(); }
	leveltype getLevel() { return pcclass->getLevel(); }
	exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
	exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
	welltype getCurrentHP() { return pcclass->HP->getCurrent(); }
	welltype getMaxHP() { return pcclass->HP->getMax(); }
	stattype getStrenght() { return pcclass->getStrength(); }
	stattype getIntellect() { return pcclass->getIntellect(); }
	stattype getAgility() { return pcclass->getAgility(); }
	stattype getArmor() { return pcclass->getArmor(); }
	stattype getElementRes() { return pcclass->getElementRes(); }

	void gainEXP(exptype amt)
	{
		pcclass->gainEXP(amt);
	}

	void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
	void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }

};

