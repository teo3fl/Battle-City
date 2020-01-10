#include "pch.h"
#include "CppUnitTest.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(PlayerTest)
	{
	public:

		TEST_METHOD(TestMethod3)
		{
			Player *player;
			player->IsProtected();
			if (player->IsProtected() == 1)
				Assert::IsTrue;
			else
				Assert::IsFalse;

		}
	};
}
