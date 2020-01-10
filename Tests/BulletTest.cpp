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


/*TEST_METHOD(DefaultConstructor)
{
	Piece piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

	Assert::IsTrue(Piece::Body::Full == piece.GetBody());
	Assert::IsTrue(Piece::Color::Dark == piece.GetColor());
	Assert::IsTrue(Piece::Height::Short == piece.GetHeight());
	Assert::IsTrue(Piece::Shape::Square == piece.GetShape());
}*/