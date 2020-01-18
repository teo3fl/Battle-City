#include "pch.h"
#include "CppUnitTest.h"
#include "Brick.h"
#include "Steel.h"
#include "Ice.h"
#include "Water.h"
#include "Trees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TileTest)
	{
	public:

		// bullet collision

		TEST_METHOD(BrickBulletCollision)
		{
			sf::Texture texture;
			Brick brick(0,0,texture);
			Assert::IsTrue(brick.GetBulletCollision());
		}

		TEST_METHOD(SteelBulletCollision)
		{
			sf::Texture texture;
			Steel steel(0, 0, texture);
			Assert::IsTrue(steel.GetBulletCollision());
		}

		TEST_METHOD(WaterBulletCollision)
		{
			sf::Texture texture;
			Water water(0, 0, texture);
			Assert::IsFalse(water.GetBulletCollision());
		}

		TEST_METHOD(IceBulletCollision)
		{
			sf::Texture texture;
			Ice ice(0, 0, texture);
			Assert::IsFalse(ice.GetBulletCollision());
		}

		TEST_METHOD(TreesBulletCollision)
		{
			sf::Texture texture;
			Trees trees(0, 0, texture);
			Assert::IsFalse(trees.GetBulletCollision());
		}


		// health

		TEST_METHOD(BrickHealth)
		{
			sf::Texture texture;
			Brick brick(0, 0, texture);
			Assert::IsTrue(brick.GetHealth()==1);
		}

		TEST_METHOD(SteelkHealth)
		{
			sf::Texture texture;
			Steel steel(0, 0, texture);
			Assert::IsTrue(steel.GetHealth() == 2);
		}

		// tank collision

		TEST_METHOD(BrickTankCollision)
		{
			sf::Texture texture;
			Brick brick(0, 0, texture);
			Assert::IsTrue(brick.GetTankCollision());
		}

		TEST_METHOD(SteelTankCollision)
		{
			sf::Texture texture;
			Steel steel(0, 0, texture);
			Assert::IsTrue(steel.GetTankCollision());
		}

		TEST_METHOD(WaterTankCollision)
		{
			sf::Texture texture;
			Water water(0, 0, texture);
			Assert::IsTrue(water.GetTankCollision());
		}

		TEST_METHOD(IceTankCollision)
		{
			sf::Texture texture;
			Ice ice(0, 0, texture);
			Assert::IsFalse(ice.GetTankCollision());
		}

		TEST_METHOD(TreesTankCollision)
		{
			sf::Texture texture;
			Trees trees(0, 0, texture);
			Assert::IsFalse(trees.GetTankCollision());
		}
	};
}
