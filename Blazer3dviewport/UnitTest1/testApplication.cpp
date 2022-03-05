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
			auto testApplication = Application::getInstance();
			testApplication->init();
			Assert::IsNotNull(testApplication->m_windows.at("main")->getWindow());
			testApplication->close();
		}
	};
}