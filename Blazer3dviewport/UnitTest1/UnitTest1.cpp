#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Sanity
{
	TEST_CLASS(SanityCheckClass)
	{
	public:
		TEST_METHOD(SanityCheck)
		{
			Assert::IsTrue(true);
		}
	};
}
