#include <iostream>
#include "playercharacter.h"

int main()
{
	PlayerCharacter p1(new Paladin());
	for (int i = 0; i < 2; i++)
	{
		std::cout
			<< p1.getClassName()
			<< " Level " << p1.getLevel() << '\n'
			<< "-EXP " << p1.getCurrentEXP() << '/' << p1.getEXPToNextLevel() << '\n'
			<< "-HP " << p1.getCurrentHP() << '/'  << p1.getMaxHP() << '\n'
			<< "-Strenght " << p1.getStrenght() << '\n'
			<< "-Agility " << p1.getAgility() << '\n'
			<< "-Intellect " << p1.getIntellect() << '\n'
			<< "-Armor " << p1.getArmor() << '\n'
			<< "-Elemental Resistance " << p1.getElementRes() << '\n';
		
		auto Abilities = p1.getAbilities();
		std::cout<<"-Abilities: \n";
		for (auto& abi : Abilities)
		{
			std::cout << " -" << abi.Name << "\n";
		}
		if (i < 1)
			p1.gainEXP(100u);
	}
	
		

	return 0;

}