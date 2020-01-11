#include "pch.h"
#include "CppUnitTest.h"
#include  "State.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(StateTest)
	{
	public:

		TEST_METHOD(VerifyVariables)
		{
			bool ok = 0;
			float m_keytime = 0.f;
			float m_keytimeMax = 20.f;

			if (m_keytime == m_keytimeMax)
				bool ok = 1;
			if (ok)
				Assert::IsFalse;
			else
				Assert::IsTrue;


		}
	};

}