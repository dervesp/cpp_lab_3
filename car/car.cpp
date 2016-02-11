#include "stdafx.h"
#include "Car.h"

std::map <CCar::Gear, CCar::SpeedRange> const CCar::gearSpeedRange =
{
	{ CCar::Gear::Rear,{ -20, 0 } },
	{ CCar::Gear::Neutral,{ -20, 150 } },
	{ CCar::Gear::First,{ 0, 30 } },
	{ CCar::Gear::Second,{ 20, 50 } },
	{ CCar::Gear::Third,{ 30, 60 } },
	{ CCar::Gear::Fourth,{ 40, 90 } },
	{ CCar::Gear::Fifth,{ 50, 150 } }
};

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(int speed)
{
	if (speed == m_speed)
	{
		return true;
	}

	if (m_gear == CCar::Gear::Neutral)
	{
		int currentAbsSpeed = std::abs(m_speed);
		int newAbsSpeed = std::abs(speed);
		if (std::abs(speed) > std::abs(m_speed))
		{
			throw std::exception("Cannot speedup on neutral gear");
			return false;
		}
	}

	if ((speed < gearSpeedRange.at(m_gear).min) || (speed > gearSpeedRange.at(m_gear).max))
	{
		throw std::exception("Cannot set this speed at this gear");
		return false;
	}

	m_speed = speed;
	return true;
}

CCar::Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(CCar::Gear gear)
{
	if (gear == m_gear)
	{
		return true;
	}

	if (gear == CCar::Gear::Rear)
	{
		if ((m_gear != CCar::Gear::Neutral) && (m_gear != CCar::Gear::First))
		{
			throw std::exception("Cannot set rear gear from this gear");
			return false;
		}
		if (GetDirection() != CCar::Direction::StandStill)
		{
			throw std::exception("Cannot set rear gear at nonzero speed");
			return false;
		}
	}

	if ((gear == CCar::Gear::First) && (m_gear == CCar::Gear::Rear))
	{
		if (GetDirection() != CCar::Direction::StandStill)
		{
			throw std::exception("Cannot set first gear from rear gear at nonzero speed");
			return false;
		}
	}

	if ((m_speed < gearSpeedRange.at(gear).min) || (m_speed > gearSpeedRange.at(gear).max))
	{
		throw std::exception("Cannot set this gear at this speed");
		return false;
	}

	m_gear = gear;
	return true;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

CCar::Direction CCar::GetDirection() const
{
	if (m_speed > 0)
	{
		return CCar::Direction::Forward;
	}
	else if (m_speed < 0)
	{
		return CCar::Direction::Backward;
	}
	return CCar::Direction::StandStill;
}

bool CCar::TurnEngineOn()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnEngineOff()
{
	bool isOnNeutralGear = (m_gear == CCar::Gear::Neutral);
	bool isOnZeroSpeed = (GetDirection() == CCar::Direction::StandStill);
	if (m_isEngineOn && isOnNeutralGear && isOnZeroSpeed)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}
