#include "pch.h"
#include "CppUnitTest.h"
#include "Tank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TankTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Tank tank;
			tank.DecreaseHealth(1);
			bool ok = 0;
			if (tank.GetHealth() == 2)
				ok = 1;
			Assert::IsTrue(ok);
		}
	};
}
