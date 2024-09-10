#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Ducks/lib/Behaviors/Dance/Waltz.h"
#include "../Ducks/lib/Behaviors/Fly/FlyWithWings.h"
#include "../Ducks/lib/Behaviors/Quack/Quake.h"
#include "../Ducks/lib/Duck/Duck.h"
#include <iostream>
#include <memory>

TEST_CASE("Creating Duck")
{
	/*
	WHEN("Dance is nullptr")
	{
		THEN("Without throw exception")
		{
			auto fn = []() {
				Duck duck(
					nullptr,
					std::make_unique<FlyWithWings>(),
					std::make_unique<QuackBehavior>());
			};

			CHECK_THROWS(fn());
		}
	}
	WHEN("Fly is nullptr")
	{
		THEN("Without throw exception")
		{
			auto fn = []() {
				Duck duck(
					std::make_unique<Waltz>(),
					nullptr,
					std::make_unique<QuackBehavior>());
			};

			CHECK_THROWS(fn());
		}
	}
	WHEN("Quack is nullptr")
	{
		THEN("Without throw exception")
		{
			auto fn = []() {
				Duck duck(
					std::make_unique<Waltz>(),
					std::make_unique<FlyWithWings>(),
					nullptr);
			};

			CHECK_THROWS(fn());
		}
	}
	*/
	WHEN("All field right")
	{
		THEN("Without throw exception")
		{
			auto fn = []() {
				Duck duck(
					std::make_unique<Waltz>(),
					std::make_unique<FlyWithWings>(),
					std::make_unique<QuackBehavior>());
			};

			CHECK_NOTHROW(fn());
		}
	}
}
