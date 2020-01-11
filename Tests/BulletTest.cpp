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
			Bullet *bullet;

			if ((BulletSource::Enemy == bullet->GetSource()))
				Assert::IsTrue;
			else
				Assert::IsTrue(BulletSource::Enemy == bullet->GetSource());

			


		}
	};

}


