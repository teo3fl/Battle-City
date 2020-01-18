#include "pch.h"
#include "CppUnitTest.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(PlayerTest)
	{
	public:

		TEST_METHOD(Protected)
		{
			Player player("Player",0,0);
			player.IsProtected();
			if (player.IsProtected() == 1)
				Assert::IsTrue;
			else
				Assert::IsFalse;
		}

		TEST_METHOD(Position)
		{
			Player player("Player", 345, 123);
			Assert::IsTrue(player.GetPosition() == sf::Vector2f(345, 123));
		}

		TEST_METHOD(Bullet)
		{
			Player player("Player", 0, 0);
			player.Fire();
			Assert::IsTrue(player.GetBullet() != nullptr);
		}

		TEST_METHOD(Score)
		{
			Player player("Player", 0, 0);
			player.IncreaseScore(500);
			Assert::IsTrue(player.GetScore() ==500);
		}

		TEST_METHOD(SecondaryBullet)
		{
			Player player("Player", 0, 0);
			Assert::IsTrue(player.CanFireSecondaryBullet() == false);
		}

		TEST_METHOD(SecondaryBullet2)
		{
			Player player("Player", 0, 0);
			player.IncreaseOffensivePower();
			player.IncreaseOffensivePower();
			Assert::IsTrue(player.CanFireSecondaryBullet() == true);
		}

		TEST_METHOD(Lives)
		{
			Player player("Player", 0, 0);
			Assert::IsTrue(player.GetLives() == 1);
		}

		TEST_METHOD(Lives2)
		{
			Player player("Player", 0, 0);
			player.GiveExtraLife();
			Assert::IsTrue(player.GetLives() == 2);
		}
	};
}
