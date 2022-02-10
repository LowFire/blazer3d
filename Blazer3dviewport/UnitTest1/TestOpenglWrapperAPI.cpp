#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>

#include "bApplication.h"
#include "VertexArray.h"

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

	TEST_CLASS(TestVertexArray)
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

		TEST_METHOD(testDefaultConstructor)
		{
			VertexArray v_arr;
			//There should be no vertex attributes in the VAO
			Assert::AreEqual(0, v_arr.vertex_attributes.size());
			Assert::AreEqual(0, v_arr.attribute_indexes.size());

			//Was the opengl name set properly?
			Assert::AreEqual(1, v_arr.getOpenglName());
			Assert::AreEqual("1", v_arr.getLabel());

			GLchar* label = new GLchar[v_arr.getLabel().size()];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.getOpenglName(),
				v_arr.getLabel().size(),
				NULL,
				label);
			Assert::AreEqual(label, v_arr.getLabel());
			delete[] label;
		}

		TEST_METHOD(testCopyConstructor)
		{
			VertexArray v_arr1;
			v_arr1.createAttribute("Positions", 4, GL_FLOAT, false, 0, (void*)(0));
			v_arr1.createAttribute("Color", 3, GL_FLOAT, false, sizeof(float)*7, (void*)(sizeof(float)*4));
			v_arr1.createAttribute("UV", 3, GL_FLOAT, false, sizeof(float)*7, (void*)(sizeof(float)*7));
			VertexArray v_arr2 = v_arr1;

			//The two objects should have the same attributes.
			Assert::AreEqual(v_arr1.vertex_attributes.size(), v_arr2.vertex_attributes.size());
			Assert::AreEqual(v_arr1.attribute_indexes.size(), v_arr2.attribute_indexes.size());

			//Those attributes should also have the same values
			auto it1 = v_arr1.vertex_attributes.begin();
			auto it2 = v_arr2.vertex_attributes.begin();
			for (; it1 != v_arr1.vertex_attributes.end() && 
				it2 != v_arr2.vertex_attributes.end(); 
				it1++, it2++)
			{
				Assert::AreEqual(it1->name, it2->name);
				Assert::AreEqual(it1->index, it2->index);
				Assert::AreEqual(it1->normalized, it2->normalized);
				Assert::AreEqual(it1->type, it2->type);
				Assert::AreEqual(it1->size, it2->size);
				Assert::AreEqual(it1->offset, it2->offset);
				Assert::AreEqual(it1->stride, it2->stride);
			}

			//Test to make sure both objects contain the same attribute indexes
			auto attrib_id1 = v_arr1.attribute_indexes.begin();
			auto attrib_id2 = v_arr2.attribute_indexes.begin();
			for (; attrib_id1 != v_arr1.attribute_indexes.end() && 
				attrib_id2 != v_arr2.attribute_indexes.end(); 
				attrib_id1++, attrib_id2++)
			{
				Assert::AreEqual(*attrib_id1, *attrib_id2);
			}

			//They should NOT have the same opengl names or labels
			Assert::AreNotEqual(v_arr1.getOpenglName(), v_arr2.getOpenglName());
			Assert::AreNotEqual(v_arr1.getLabel(), v_arr2.getLabel());

			//Make sure the object lables for both objects are properly set
			GLchar* vao1_label = new GLchar[v_arr1.getLabel().size()];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr1.getOpenglName(),
				v_arr1.getLabel().size(),
				NULL,
				vao1_label);
			Assert::AreEqual(label, v_arr1.getLabel());
			delete[] vao1_label;

			GLchar* vao2_label = new GLchar[v_arr2.getLabel().size()];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr2.getOpenglName(),
				v_arr2.getLabel().size(),
				NULL,
				vao2_label);
			Assert::AreEqual(label, v_arr2.getLabel());
			delete[] vao2_label;
		}

		TEST_METHOD(testNameConstructor)
		{
			VertexArray v_arr("SoldierModel");

			//Test if the label was set properly
			Assert::AreEqual("SoldierModel", v_arr.getLabel());
			GLchar* label = new GLchar[v_arr.getLabel().size()];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.getOpenglName(),
				v_arr.getLabel().size(),
				NULL,
				label);
			Assert::AreEqual(label, v_arr.getLabel());
			delete[] label;

			//There should be no vertex attributes in the VAO
			Assert::AreEqual(0, v_arr.vertex_attributes.size());
			Assert::AreEqual(0, v_arr.attribute_indexes.size());
			
			//Was the opengl name set properly?
			Assert::AreEqual(1, v_arr.getOpenglName());
		}
		
		TEST_METHOD(testInitListConstructor)
		{

		}

		TEST_METHOD(testBind)
		{

		}

		TEST_METHOD(testEnableAndDisableAttribute)
		{

		}

		TEST_METHOD(testSetGenericAttribute)
		{

		}

		TEST_METHOD(testGetOpenglName)
		{

		}

		TEST_METHOD(testSetAndGetLabel)
		{

		}

		TEST_METHOD(testCreateAttribute)
		{

		}
	};
}