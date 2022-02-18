#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>

#include "Application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestApplication)
	{
	public:

		TEST_METHOD(TestInit)
		{
			Application testApplication;
			testApplication.init();
			Assert::IsNotNull(testApplication.windows.at("main")->getWindow());
			testApplication.close();
		}
	};
}