#include "stdafx.h"
#include "Car.h"


int CCar::GetSpeed() const
{
	return m_speed;
}

CCar::Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
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
