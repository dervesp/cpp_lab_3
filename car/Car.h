#pragma once
#include <map>

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

	enum class Direction
	{
		Forward = 1,
		StandStill = 0,
		Backward = -1
	};

	struct SpeedRange
	{
		int min, max;
	};

	int GetSpeed() const;
	bool SetSpeed(int speed);

	Gear GetGear() const;
	bool SetGear(Gear gear);

	bool IsEngineOn() const;
	Direction GetDirection() const;

	bool TurnEngineOn();
	bool TurnEngineOff();

	static const std::map <Gear, SpeedRange> gearSpeedRange;
private:
	int m_speed = 0;
	Gear m_gear = Gear::Neutral;
	bool m_isEngineOn = false;
};

