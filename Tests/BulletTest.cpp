#include "pch.h"

#include "CppUnitTest.h"
#include "Bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(BulletTest)
	{
	public:

		TEST_METHOD(DefaultConstructor)
		{
			sf::Texture texture;
			Bullet bullet(0,0,1,sf::Vector2f(0,1),texture,BulletType::Normal,BulletSource::Enemy);

			if ((BulletSource::Enemy == bullet.GetSource()))
				Assert::IsTrue;
			else
				Assert::IsTrue(BulletSource::Enemy == bullet.GetSource());
		}
	};

}


