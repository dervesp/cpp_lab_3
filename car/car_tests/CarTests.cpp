#include "stdafx.h"
#include "../Car.h"


struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
	BOOST_AUTO_TEST_CASE(by_default_engine_is_off)
	{
		BOOST_CHECK(!car.IsEngineOn());
	}
	BOOST_AUTO_TEST_CASE(by_default_gear_is_neutral)
	{
		BOOST_CHECK(car.GetGear() == CCar::Gear::Neutral);
	}

	BOOST_AUTO_TEST_CASE(by_default_speed_is_zero)
	{
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_turn_engine_on)
	{
		BOOST_CHECK(car.TurnEngineOn);
		BOOST_CHECK(car.IsEngineOn());
	}
BOOST_AUTO_TEST_SUITE_END()