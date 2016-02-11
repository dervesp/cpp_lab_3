#include "stdafx.h"
#include "../Car.h"
#include <string>

using Direction = CCar::Direction;
using Gear = CCar::Gear;

void CheckGear(CCar & car, CCar::Gear gear)
{
	BOOST_CHECK(car.GetGear() == gear);
}

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
		CheckGear(car, CCar::Gear::Neutral);
	}

	BOOST_AUTO_TEST_CASE(by_default_speed_is_zero)
	{
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_turn_engine_on)
	{
		BOOST_CHECK(car.TurnEngineOn());
		BOOST_CHECK(car.IsEngineOn());
		BOOST_CHECK(!car.TurnEngineOn());
	}

	BOOST_AUTO_TEST_CASE(can_turn_engine_off)
	{
		BOOST_CHECK(car.TurnEngineOn());
		BOOST_CHECK(car.TurnEngineOff());
		BOOST_CHECK(!car.IsEngineOn());
		BOOST_CHECK(!car.TurnEngineOff());
	}

	BOOST_AUTO_TEST_CASE(can_turn_engine_off_only_on_neutral_gear_and_zero_speed)
	{
		BOOST_CHECK(car.TurnEngineOn());
		BOOST_CHECK(car.SetGear(CCar::Gear::First));
		BOOST_CHECK(car.SetSpeed(30));
		BOOST_CHECK(!car.TurnEngineOff());
	}

	struct with_engine_on_ : CarFixture
	{
		with_engine_on_()
		{
			car.TurnEngineOn();
		}

		template <typename Fn>
		void ExpectActionFailure(Fn && action)
		{
			CCar clone(car);
			BOOST_CHECK_THROW(action(), std::exception);
			BOOST_REQUIRE_EQUAL(clone.IsEngineOn(), car.IsEngineOn());
			if (clone.IsEngineOn())
			{
				BOOST_CHECK(clone.GetDirection() == car.GetDirection());
				BOOST_CHECK(clone.GetGear() == car.GetGear());
				BOOST_CHECK(clone.GetSpeed() == car.GetSpeed());
			}
		}

		template <typename Fn>
		void ExpectActionSucceeds(Fn && action, bool expectEngineIsOn, CCar::Gear expectedGear, int expectedSpeed)
		{
			BOOST_REQUIRE_NO_THROW(action());
			BOOST_REQUIRE_EQUAL(car.IsEngineOn(), expectEngineIsOn);
			if (expectEngineIsOn)
			{
				BOOST_CHECK(car.GetGear() == expectedGear);
				BOOST_CHECK_EQUAL(car.GetSpeed(), expectedSpeed);
				auto expectedDirection =
					(expectedSpeed > 0) ? Direction::Forward :
					(expectedSpeed < 0) ? Direction::Backward :
					Direction::StandStill;
				BOOST_CHECK(car.GetDirection() == expectedDirection);
			}
		}

		//void CheckGearRange(CCar & car, CCar::Gear expectedGear, int speedMin, int speedMax)
		//{
		//	CheckGear(car, expectedGear);
		//	ExpectActionFailure([=] { car.SetSpeed(speedMin - 1); });
		//	ExpectActionSucceeds([=] { car.SetSpeed(speedMin); }, true, expectedGear, speedMin);
		//	ExpectActionSucceeds([=] { car.SetSpeed(speedMax); }, true, expectedGear, speedMax);
		//	ExpectActionFailure([=] { car.SetSpeed(speedMax + 1); });
		//}
	};
	
	BOOST_FIXTURE_TEST_SUITE(with_engine_on, with_engine_on_)
		BOOST_AUTO_TEST_CASE(cannot_speedup_at_neutral_gear)
		{
			ExpectActionFailure([=] { car.SetSpeed(10); });
		}

		BOOST_AUTO_TEST_CASE(can_switch_to_first_gear)
		{
			ExpectActionSucceeds([=] {
				car.SetGear(CCar::Gear::First);
			}, true, CCar::Gear::First, 0);
		}

		BOOST_AUTO_TEST_CASE(can_switch_speed_in_gear_range)
		{
			car.SetGear(CCar::Gear::First);
			car.SetSpeed(30);

			int speedMin, speedMax;
			Gear expectedGear;

			expectedGear = CCar::Gear::Second;
			car.SetGear(expectedGear);
			speedMin = 20;
			speedMax = 50;
			CheckGear(car, expectedGear);
			ExpectActionFailure([=] { car.SetSpeed(speedMin - 1); });
			ExpectActionSucceeds([=] { car.SetSpeed(speedMin); }, true, expectedGear, speedMin);
			ExpectActionSucceeds([=] { car.SetSpeed(speedMax); }, true, expectedGear, speedMax);
			ExpectActionFailure([=] { car.SetSpeed(speedMax + 1); });

			expectedGear = CCar::Gear::Third;
			car.SetGear(expectedGear);
			speedMin = 30;
			speedMax = 60;
			CheckGear(car, expectedGear);
			ExpectActionFailure([=] { car.SetSpeed(speedMin - 1); });
			ExpectActionSucceeds([=] { car.SetSpeed(speedMin); }, true, expectedGear, speedMin);
			ExpectActionSucceeds([=] { car.SetSpeed(speedMax); }, true, expectedGear, speedMax);
			ExpectActionFailure([=] { car.SetSpeed(speedMax + 1); });

			expectedGear = CCar::Gear::Fourth;
			car.SetGear(expectedGear);
			speedMin = 40;
			speedMax = 90;
			CheckGear(car, expectedGear);
			ExpectActionFailure([=] { car.SetSpeed(speedMin - 1); });
			ExpectActionSucceeds([=] { car.SetSpeed(speedMin); }, true, expectedGear, speedMin);
			ExpectActionSucceeds([=] { car.SetSpeed(speedMax); }, true, expectedGear, speedMax);
			ExpectActionFailure([=] { car.SetSpeed(speedMax + 1); });

			expectedGear = CCar::Gear::Fifth;
			car.SetGear(expectedGear);
			speedMin = 50;
			speedMax = 150;
			CheckGear(car, expectedGear);
			ExpectActionFailure([=] { car.SetSpeed(speedMin - 1); });
			ExpectActionSucceeds([=] { car.SetSpeed(speedMin); }, true, expectedGear, speedMin);
			ExpectActionSucceeds([=] { car.SetSpeed(speedMax); }, true, expectedGear, speedMax);
			ExpectActionFailure([=] { car.SetSpeed(speedMax + 1); });
		}

		BOOST_AUTO_TEST_CASE(can_switch_gear_only_in_gear_range)
		{
			car.SetGear(CCar::Gear::Rear);
			car.SetSpeed(-1);
			ExpectActionFailure([=] { car.SetGear(Gear::First); });
			car.SetSpeed(0);
			ExpectActionSucceeds([=] { car.SetGear(Gear::First); }, true, Gear::First, 0);

			car.SetSpeed(19);
			ExpectActionFailure([=] { car.SetGear(Gear::Second); });
			car.SetSpeed(20);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Second); }, true, Gear::Second, 20);

			car.SetSpeed(29);
			ExpectActionFailure([=] { car.SetGear(Gear::Third); });
			car.SetSpeed(30);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Third); }, true, Gear::Third, 30);

			car.SetSpeed(39);
			ExpectActionFailure([=] { car.SetGear(Gear::Fourth); });
			car.SetSpeed(40);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Fourth); }, true, Gear::Fourth, 40);

			car.SetSpeed(49);
			ExpectActionFailure([=] { car.SetGear(Gear::Fifth); });
			car.SetSpeed(50);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Fifth); }, true, Gear::Fifth, 50);

			car.SetSpeed(91);
			ExpectActionFailure([=] { car.SetGear(Gear::Fourth); });
			car.SetSpeed(90);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Fourth); }, true, Gear::Fourth, 90);

			car.SetSpeed(61);
			ExpectActionFailure([=] { car.SetGear(Gear::Third); });
			car.SetSpeed(60);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Third); }, true, Gear::Third, 60);

			car.SetSpeed(51);
			ExpectActionFailure([=] { car.SetGear(Gear::Second); });
			car.SetSpeed(50);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Second); }, true, Gear::Second, 50);

			car.SetSpeed(31);
			ExpectActionFailure([=] { car.SetGear(Gear::First); });
			car.SetSpeed(30);
			ExpectActionSucceeds([=] { car.SetGear(Gear::First); }, true, Gear::First, 30);
		}

		BOOST_AUTO_TEST_CASE(can_switch_to_rear_gear_only_from_first_or_neutral_gear_while_standing)
		{
			car.SetGear(Gear::First);
			CheckGear(car, Gear::First);
			car.SetSpeed(20);
			car.SetGear(Gear::Second);
			ExpectActionFailure([=] { car.SetGear(Gear::Rear); });
			car.SetGear(Gear::First);
			ExpectActionFailure([=] { car.SetGear(Gear::Rear); });
			car.SetGear(Gear::Neutral);
			ExpectActionFailure([=] { car.SetGear(Gear::Rear); });
			car.SetSpeed(0);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Rear); }, true, Gear::Rear, 0);
			car.SetGear(Gear::First);
			ExpectActionSucceeds([=] { car.SetGear(Gear::Rear); }, true, Gear::Rear, 0);
		}

		BOOST_AUTO_TEST_CASE(can_switch_to_first_gear_from_rear_gear_only_while_standing)
		{
			car.SetGear(Gear::Rear);
			car.SetSpeed(-20);
			ExpectActionFailure([=] { car.SetGear(Gear::First); });
			car.SetSpeed(0);
			ExpectActionSucceeds([=] { car.SetGear(Gear::First); }, true, Gear::First, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()