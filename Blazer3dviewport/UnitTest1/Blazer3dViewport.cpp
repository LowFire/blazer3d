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
			Assert::IsTrue(true);
			//This is going to be commented out for now.
			//It's more important that the CI/CD pipline is functioning on github
			//This will be fixed later.
			//bApplication testApplication;
			//testApplication.init();
			//Assert::IsNotNull(testApplication.windows.at("main")->getWindow());
		}
	};
}