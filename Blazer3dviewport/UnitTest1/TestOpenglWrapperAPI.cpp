#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <array>
#include <string>

#include "bApplication.h"
#include "bVertexArrayObjects.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{ 
	TEST_CLASS(TestbApplication)
	{
	public:

		TEST_METHOD(TestInit)
		{
			bApplication testApplication;
			testApplication.init();
			Assert::IsNotNull(testApplication.windows.at("main")->getWindow());
			testApplication.close();
		}
	};

	TEST_CLASS(TestbVertexArrayObjects)
	{
	private:
		static bApplication test_application;

	public:

		TEST_CLASS_INITIALIZE(InitApplication)
		{
			test_application.init();
		}

		TEST_CLASS_CLEANUP(DestroyApplication)
		{
			test_application.close();
		}

		TEST_METHOD(TestContruction)
		{

			/*
			* Test default constructor
			*/
			auto default_construtor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects);
			Assert::AreEqual(0, default_construtor->size()); //Check to ensure the there are no VAOs created.


			/*
			* Test non-default constructor that takes in the number of VAOs to create.
			*/
			auto sized_constructor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(5));
			Assert::AreEqual(5, sized_constructor->size()); //Check if the correct number of objects are constructed;
			auto vertex_arrays = sized_construtor->getAllVertexArrays(); //Returns the vector of shared pointers to bVertexArrays

			//Test to see if all objects are valid
			for each (auto v in vertex_arrays)
			{
				Assert::IsNotNull(v);
				vertex_arrays.at(i)->bind();
				Assert::IsTrue(glIsVertexArray(v->getOpenglName()));
			}

			/*
			* Test non-default constructor that takes in the number of VAOs and an array of names to give each VAO
			*/
			std::array<const char*, 3> names = { "Cube", "Pyramid", "Sphere" };
			auto named_constructor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(3, names));
			Assert::AreEqual(3, named_constructor->size());
			vertex_arrays = named_constructor->getAllVertexArrays();

			//Test to make sure each vertex array is constructed properly.
			for(int i = 0; i < 3; i++)
			{
				Assert::IsNotNull(vertex_arrays.at(i));
				vertex_arrays.at(i)->bind();
				Assert::IsTrue(glIsVertexArray(vertex_arrays.at(i)->getOpenglName()));
				Assert::AreEqual(vertex_arrays.at(i)->getLabel(), names[i]);
			}
		}

		TEST_METHOD(TestDestruction)
		{
			auto test_object = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(3));
			auto array_references = test_object->getAllVertexArrays();
			test_object->~bVertexArrayObjects(); //Call the destructor
			
			for each (auto v in array_references)
			{
				Assert::IsNull(v);
				Assert::IsFalse(glIsVertexArray(v->))
			}


		}
	};
}