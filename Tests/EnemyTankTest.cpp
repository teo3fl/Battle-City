#include "pch.h"
#include "CppUnitTest.h"
#include "ArmorTank.h"
#include "BasicTank.h"
#include "FastTank.h"
#include "PowerTank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(EnemyTankTest)
	{
	public:

		TEST_METHOD(BasicTankType)
		{
			BasicTank basicTank;
			Assert::IsTrue(basicTank.GetType() == "BasicTank");
		}

		TEST_METHOD(FastTankSpeed)
		{
			FastTank fastTank;
			Assert::IsTrue(fastTank.GetMovement() == 150.f);
		}

		TEST_METHOD(PowerTankPoints)
		{
			PowerTank powerTank;
			Assert::IsTrue(powerTank.GetPoints() == 300);
		}
	};
}
