#include "pch.h"
#include "CppUnitTest.h"

#include "bApplication.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Blazer3dviewport
{ 
	TEST_CLASS(TestbApplication)
	{
	public:

		TEST_METHOD(TestInit)
		{
			bApplication testApplication;
			testApplication.init();
			Assert::IsNotNull(testApplication.windows.at("main")->getWindow());
		}
	};
}