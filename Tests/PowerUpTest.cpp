#include "pch.h"
#include "CppUnitTest.h"
#include  "PowerUp.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(PowerUp)
	{
	public:

		TEST_METHOD(Update)
		{
			
			PowerUp power_up;
			if (power_up.Update)
				Assert::IsTrue;
			else
				Assert::IsFalse;

		}
	};

}