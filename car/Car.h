#pragma once

class CCar
{
public:

	enum class Gear
	{
		Rear = -1,
		Neutral = 0,
		First = 1,
		Second = 2,
		Third = 3,
		Fourth = 4,
		Fifth = 5
	};

	int GetSpeed() const;
	Gear GetGear() const;
	bool IsEngineOn() const;

	bool TurnEngineOn();

private:
	int m_speed = 0;
	Gear m_gear = Gear::Neutral;
	bool m_isEngineOn = false;
};

