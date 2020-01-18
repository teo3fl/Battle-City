#include "pch.h"

#include "CppUnitTest.h"
#include "Bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(BulletTest)
	{
	public:

		TEST_METHOD(Position)
		{
			sf::Texture texture;
			Bullet bullet(0, 0, 1, sf::Vector2f(0, 1), texture, BulletType::Normal, BulletSource::Enemy);
			Assert::IsTrue(bullet.GetPosition() == sf::Vector2f(0,0));
		}

		TEST_METHOD(Health)
		{
			sf::Texture texture;
			Bullet bullet(0, 0, 1, sf::Vector2f(0, 1), texture, BulletType::Normal, BulletSource::Enemy);
			uint8_t expectedHealth = 1;
			Assert::IsTrue(bullet.GetHealth() == expectedHealth);
		}
		TEST_METHOD(DecreasingHealth)
		{
			sf::Texture texture;
			Bullet bullet(0, 0, 2, sf::Vector2f(0, 1), texture, BulletType::Normal, BulletSource::Enemy);
			bullet.DecreaseHealth(1);
			uint8_t expectedHealth = 1;
			Assert::IsTrue(bullet.GetHealth() == expectedHealth);
		}
	};
}


