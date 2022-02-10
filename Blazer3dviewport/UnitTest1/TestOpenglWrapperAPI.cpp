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

	//TEST_CLASS(TestbVertexArrayObjects)
	//{
	//private:
	//	static bApplication test_application;

	//public:

	//	TEST_CLASS_INITIALIZE(InitApplication)
	//	{
	//		test_application.init();
	//	}

	//	TEST_CLASS_CLEANUP(DestroyApplication)
	//	{
	//		test_application.close();
	//	}

	//	TEST_METHOD(TestContruction)
	//	{

	//		/*
	//		* Test default constructor
	//		*/
	//		auto default_construtor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects);
	//		Assert::AreEqual(0, default_construtor->size()); //Check to ensure the there are no VAOs created.

	//		/*
	//		* Test non-default constructor that takes in the number of VAOs to create.
	//		*/
	//		auto sized_constructor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(5));
	//		Assert::AreEqual(5, sized_constructor->size()); //Check if the correct number of objects are constructed;
	//		auto vertex_arrays = sized_constructor->getAllVertexArrays(); //Returns the vector of weak pointers to bVertexArrays

	//		//Test to see if all objects are valid
	//		for each (auto v in vertex_arrays)
	//		{
	//			auto ptr = v.lock();
	//			Assert::IsTrue(ptr!=nullptr);
	//			ptr->bind();
	//			Assert::IsTrue(glIsVertexArray(ptr->getOpenglName()));
	//		}

	//		/*
	//		* Test non-default constructor that takes in a list of labels.
	//		*/
	//		auto named_constructor = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects{ "Cube", "Pyramid", "Sphere" });
	//		Assert::AreEqual(3, named_constructor->size());
	//		vertex_arrays = named_constructor->getAllVertexArrays();

	//		//Test to make sure each vertex array is constructed properly.
	//		for each (auto v in vertex_arrays)
	//		{
	//			auto ptr = v.lock();
	//			Assert::IsTrue(ptr!=nullptr);
	//			ptr->bind();
	//			Assert::IsTrue(glIsVertexArray(ptr->getOpenglName()));
	//		}

	//		//Test to see if the labels have been initialized.
	//		auto ptr = vertex_arrays.at(0).lock();
	//		GLchar* cube_label = new GLchar[4];
	//		Assert::AreEqual("Cube", ptr->label.c_str());
	//		glGetObjectLabel(GL_VERTEX_ARRAY,
	//			ptr->opengl_name,
	//			4,
	//			NULL,
	//			cube_label);
	//		Assert::AreEqual(ptr->label.c_str(), cube_label);
	//		delete[] cube_label;

	//		ptr = vertex_arrays.at(1).lock();
	//		GLchar* pyramid_label = new GLchar[7];
	//		Assert::AreEqual("Cube", ptr->label.c_str());
	//		glGetObjectLabel(GL_VERTEX_ARRAY,
	//			ptr->opengl_name,
	//			7,
	//			NULL,
	//			cube_label);
	//		Assert::AreEqual(ptr->label.c_str(), pyramid_label);
	//		delete[] pyramid_label;

	//		ptr = vertex_arrays.at(2).lock();
	//		GLchar* sphere_label = new GLchar[6];
	//		Assert::AreEqual("Cube", ptr->label.c_str());
	//		glGetObjectLabel(GL_VERTEX_ARRAY,
	//			ptr->opengl_name,
	//			7,
	//			NULL,
	//			cube_label);
	//		Assert::AreEqual(ptr->label.c_str(), pyramid_label);
	//		delete[] sphere_label;


	//		/*
	//		* Test copy construction
	//		*/
	//		auto object1 = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(3));
	//		auto object2 = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(*object1));
	//		Assert::AreEqual(object1->size(), object2->size());

	//		auto obj1_references = object1->getAllVertexArrays();
	//		auto obj2_references = object2->getAllVertexArrays();
	//		auto it1 = obj1_references.begin();
	//		auto it2 = obj2_references.begin();
	//		
	//		//Check to see if the two objects have references to the same VAOs
	//		for (; it1 != obj1_references.end() && it2 != obj2_references.end();
	//			it1++, it2++)
	//		{
	//			auto ptr1 = it1->lock();
	//			auto ptr2 = it2->lock();
	//			Assert::AreSame(ptr1, ptr2);
	//		}
	//	}

	//	TEST_METHOD(TestCleanup)
	//	{
	//		/*
	//		* Test basic cleanup.
	//		*/
	//		auto test_object = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(3));
	//		auto array_references = test_object->getAllVertexArrays();
	//		test_object->~bVertexArrayObjects(); //Call the destructor
	//		
	//		for each (auto v in array_references)
	//		{
	//			Assert::IsTrue(v.expired());
	//		}

	//		/*
	//		* Test cleanup of two objects that have both shared references and unique ones.
	//		*/
	//		auto obj1 = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(3));
	//		auto obj2 = std::make_unique<bVertexArrayObjects>(new bVertexArrayObjects(*obj1));
	//		obj1->createVertexArrays(1);
	//		obj2->createVertexArrays(1);
	//		auto obj1_refs = obj1->getAllVertexArrays();
	//		auto obj2_refs = obj2->getAllVertexArrays();

	//		//Call destructor of first object
	//		obj1->~bVertexArrayObjects();

	//		//Check the references of the first object.
	//		Assert::IsFalse(obj1_refs.at(0).expired());
	//		Assert::IsFalse(obj1_refs.at(1).expired());
	//		Assert::IsFalse(obj1_refs.at(2).expired());
	//		Assert::IsTrue(obj1_refs.at(3).expired()); //The last one should have expired

	//		//Call destructor of the second object
	//		obj2->~bVertexArrayObjects();

	//		//Check the references of the second object;
	//		for each (auto v in obj2_refs)
	//		{
	//			//All references should be expired
	//			Assert::IsTrue(v.expired());
	//		}
	//	}
	//};
}