#pragma once
#include <cstdint>
#include "pointwell.h"
#include "statblock.h"
#include <string>
#include <memory>
#include "ability.h"
#include <vector>

typedef std::uint16_t leveltype;
typedef std::uint64_t exptype;

class PlayerCharacterDelegate : public StatBlock
{

public:
	
	static const exptype LEVEL2AT = 100u;

	PlayerCharacterDelegate() : StatBlock(0u, 0u)
	{
		CurrentLevel = (leveltype)1u;
		CurrentEXP = (exptype)0u;
		EXPToNextLevel = LEVEL2AT;
		HP = std::make_unique<PointWell>(1u, 1u);
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

	std::unique_ptr <PointWell> HP;
	std::unique_ptr <PointWell> MP;

	std::vector<Ability> Abilities;

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

#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increaseCurrent(BASEHP);\
if(MP)\
{\
	MP->setMax(BASEMP);\
	MP->increaseCurrent(BASEMP);\
}\
increaseStats(BASESTR, BASEAGI, BASEINT);\

#define LEVELUP \
HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax()));\
HP->increaseCurrent((welltype)(BASEHP / 2.f));\
if(MP)\
{\
	MP->setMax((welltype)((BASEMP / 2.f) + HP->getMax())); \
	MP->increaseCurrent((welltype)(BASEMP / 2.f)); \
}\
increaseStats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f));\

class Warrior : public PlayerCharacterDelegate {

public:
	static const welltype BASEHP = (welltype)14u;
	static const welltype BASEMP = (stattype)10u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEAGI = (stattype)5u;
	static const stattype BASEINT = (stattype)5u;
	std::string getClassName() override { return std::string("Warrior"); }
	Warrior() : PlayerCharacterDelegate()
	{
		//MP = std::make_unique<PointWell>(BASEMP, BASEMP);// must init before pcconstruct macro
		PCCONSTRUCT
		Abilities.emplace_back("Heroic Strike", 0u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);
		
	}
private:
	void LevelUp() override
	{
		LEVELUP
			if (CurrentLevel == 2)
			{
				Abilities.emplace_back("Slam", 0u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);
			}
	}
};

class Paladin : public PlayerCharacterDelegate {
	
public:
		static const welltype BASEHP = (welltype)14u;
		static const welltype BASEMP = (stattype)10u;
		static const stattype BASESTR = (stattype)3u; 
		static const stattype BASEAGI = (stattype)5u; 
		static const stattype BASEINT = (stattype)5u; 
		std::string getClassName() override { return std::string("Paladin"); }
		Paladin() : PlayerCharacterDelegate()
		{
			MP = std::make_unique<PointWell>(BASEMP,BASEMP);// must init before pcconstruct macro
			PCCONSTRUCT
			Abilities.emplace_back("Crusader's Strike", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);
			Abilities.emplace_back("Heal", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALAR::INT);
		}
private:
	void LevelUp() override 
	{
		LEVELUP
		if (CurrentLevel == 2)
		{
			Abilities.emplace_back("Judgement", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);
		}
	}
};

class Rogue : public PlayerCharacterDelegate {

public:
	static const welltype BASEHP = (welltype)14u;
	static const welltype BASEMP = (stattype)10u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEAGI = (stattype)5u;
	static const stattype BASEINT = (stattype)5u;
	std::string getClassName() override { return std::string("Rogue"); }
	Rogue() : PlayerCharacterDelegate()
	{
		//MP = std::make_unique<PointWell>(BASEMP, BASEMP);// must init before pcconstruct macro
		PCCONSTRUCT
		Abilities.emplace_back("Slash", 0u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);

	}
private:
	void LevelUp() override
	{
		LEVELUP
			if (CurrentLevel == 2)
			{
				Abilities.emplace_back("Pierce", 0u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALAR::STR);
			}
	}
};

class Wizard : public PlayerCharacterDelegate {

public:
	static const welltype BASEHP = (welltype)14u;
	static const welltype BASEMP = (stattype)10u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEAGI = (stattype)5u;
	static const stattype BASEINT = (stattype)5u;
	std::string getClassName() override { return std::string("Wizard"); }
	Wizard() : PlayerCharacterDelegate()
	{
		MP = std::make_unique<PointWell>(BASEMP, BASEMP);// must init before pcconstruct macro
		PCCONSTRUCT
		Abilities.emplace_back("Firebolt", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALAR::STR);
		//Abilities.emplace_back("Frost Shield", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALAR::INT); 
	}
private:
	void LevelUp() override
	{
		LEVELUP
			if (CurrentLevel == 2)
			{
				Abilities.emplace_back("Fire Blast", 5u, 2u, ABILITYTARGET::ENEMY, 5u, ABILITYSCALAR::STR);
			}
	}
};

class Cleric : public PlayerCharacterDelegate {

public:
	static const welltype BASEHP = (welltype)14u;
	static const welltype BASEMP = (stattype)10u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEAGI = (stattype)5u;
	static const stattype BASEINT = (stattype)5u;
	std::string getClassName() override { return std::string("Cleric"); }
	Cleric() : PlayerCharacterDelegate()
	{
		MP = std::make_unique<PointWell>(BASEMP, BASEMP);// must init before pcconstruct macro
		PCCONSTRUCT
		Abilities.emplace_back("Smite", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALAR::STR);
		Abilities.emplace_back("Heal", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALAR::INT); 
	}
private:
	void LevelUp() override
	{
		LEVELUP
			if (CurrentLevel == 2)
			{
				Abilities.emplace_back("Holy Blast", 3u, 2u, ABILITYTARGET::ENEMY, 3u, ABILITYSCALAR::STR);
			}
	}
};
 
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

	welltype getCurrentMP() 
	{ 
		if (pcclass->MP)
		{
			return pcclass->MP->getCurrent();
		}
		else
			return 0;
	}
	welltype getMaxMP() 
	{ 
		if (pcclass->MP) 
		{
			return pcclass->MP->getMax();
		}
		else
			return 0;
	}

	stattype getStrenght() { return pcclass->getStrength(); }
	stattype getIntellect() { return pcclass->getIntellect(); }
	stattype getAgility() { return pcclass->getAgility(); }
	stattype getArmor() { return pcclass->getArmor(); }
	stattype getElementRes() { return pcclass->getElementRes(); }

	std::vector<Ability> getAbilities() { return pcclass->Abilities; }

	void gainEXP(exptype amt){ pcclass->gainEXP(amt); }
	void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
	void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }

};

