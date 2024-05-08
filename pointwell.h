#pragma once
#include <cstdint>

typedef std::uint32_t welltype;

class PointWell
{
public:

	bool setMax(welltype newMax)
	{
		if (newMax < 1)
		{
			return false;
		}

		MaxWell = newMax;

		if (CurrentFullness > MaxWell)
		{
			CurrentFullness = MaxWell;
		}
		return true;
	}

	welltype getMax() 
	{
		return MaxWell;
	}

	welltype getCurrent()
	{
		return CurrentFullness;
	}

	void reduceCurrent(welltype damage)
	{
		if (damage > CurrentFullness)
		{
			CurrentFullness = 0;
			return;
		}

		CurrentFullness -= damage;
	}

	void increaseCurrent(welltype amount)
	{
		if (CurrentFullness + amount > MaxWell)
		{
			CurrentFullness = MaxWell;
			return;
		}

		CurrentFullness += amount;

	}
	
	PointWell() {
		CurrentFullness = 1;
		MaxWell = 1;
	}

	PointWell(welltype c, welltype m)
	{
		CurrentFullness = c;
		MaxWell = m;

		if (CurrentFullness > MaxWell)
		{
			CurrentFullness = MaxWell;
		}
	}

private:
	welltype CurrentFullness;
	welltype MaxWell;

};