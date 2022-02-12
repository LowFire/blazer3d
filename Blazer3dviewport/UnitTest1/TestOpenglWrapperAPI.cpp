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
			VertexArray v_arr {
				{ "Positions", 0, 4, GL_FLOAT, false, 0, (void*)(0) },
				{ "Color", 1, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
				{ "UV", 2, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 7) }
			};

			//Test if all vertex attributes have been initialized properly
			Assert::AreEqual("Positions", v_arr.getAttribute(0).name.c_str());
			Assert::AreEqual(0, v_arr.getAttribute(0).index);
			Assert::AreEqual(4, v_arr.getAttribute(0).size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute(0).type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute(0).normalized);
			Assert::AreEqual(0, v_arr.getAttribute(0).stride);
			Assert::AreEqual((const void*)(0), v_arr.getAttribute(0).offset);

			Assert::AreEqual("Color", v_arr.getAttribute(1).name.c_str());
			Assert::AreEqual(1, v_arr.getAttribute(1).index);
			Assert::AreEqual(3, v_arr.getAttribute(1).size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute(1).type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute(1).normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 7), v_arr.getAttribute(1).stride);
			Assert::AreEqual((void*)(sizeof(float) * 4), v_arr.getAttribute(1).offset);

			Assert::AreEqual("UV", v_arr.getAttribute(2).name.c_str());
			Assert::AreEqual(2, v_arr.getAttribute(2).index);
			Assert::AreEqual(3, v_arr.getAttribute(2).size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute(2).type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute(2).normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 7), v_arr.getAttribute(2).stride);
			Assert::AreEqual((void*)(sizeof(float) * 7), v_arr.getAttribute(2).offset);
		}

		TEST_METHOD(testBindAndUnbind)
		{
			VertexArray v_arr1;
			VertexArray v_arr2;
			v_arr1.bind();
			Assert::IsTrue(v_arr1.isBound());
			Assert::IsFalse(v_arr2.isBound());
			v_arr2.bind();
			Assert::IsFalse(v_arr1.isBound());
			Assert::IsTrue(v_arr2.isBound());
			v_arr1.unbind(); //This call should not unbind the currently bound VAO.
			Assert::IsTrue(v_arr2.isBound());
			v_arr2.unbind();
			Assert::IsFalse(v_arr2.isBound());
		}

		TEST_METHOD(testEnableAndDisableAttribute)
		{
			VertexArray v_arr {
				{ "Positions", 0, 4, GL_FLOAT, false, 0, (void*)(0) },
				{ "Color", 1, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
				{ "UV", 2, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 7) }
			};

			v_arr.bind();

			v_arr.enableAttribute("Positions");
			v_arr.enableAttribute("Color");
			v_arr.enableAttribute(2); //test if indexing works.

			for each (auto v in v_arr.vertex_attributes)
			{
				GLint state;
				glGetVertexAttribiv(v.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &state);
				Assert::IsFalse(state == GL_TRUE ? true : false);
			}

			v_arr.disableAttribute("Positions");
			v_arr.disableAttribute("Color");
			v_arr.disableAttribute(2);

			for each (auto v in v_arr.vertex_attributes)
			{
				GLint state;
				glGetVertexAttribiv(v.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &state);
				Assert::IsFalse(state == GL_TRUE ? true : false);
			}
		}

		TEST_METHOD(testSetGenericAttribute)
		{
			VertexArray v_arr {
				{ "Positions", 0, 4, GL_FLOAT, false, 0, (void*)(0) },
				{ "Color", 1, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
			};

			//Test with a brace list of values.
			v_arr.setGenericAttribute("Color", { 0.5f, 0.2f, 0.0f });
			v_arr.setGenericAttribute(0, { 5.0f, 5.0f, 2.0f });

			float* actualPos;
			float* expectedPos = new float[]{ 5.0f, 5.0f, 2.0f };
			glGetVertexAttribfv(v_arr.getAttribute("Positions").index, GL_CURRENT_VERTEX_ATTRIB, actualPos);

			bool same = true;
			for (int i = 0; i < 3; i++)
			{
				if (expectedPos[i] != actualPos[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);

			float* actualCol;
			float* expectedCol = new float[] { 0.5f, 0.2f, 0.0f };
			glGetVertexAttribfv(v_arr.getAttribute("Color").index, GL_CURRENT_VERTEX_ATTRIB, actualCol);

			same = true;
			for (int i = 0; i < 3; i++)
			{
				if (expectedPos[i] != actualPos[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);

			delete[] expectedPos;
			delete[] expectedCol;
		}

		TEST_METHOD(testGetOpenglName)
		{
			VertexArray v_arr1;
			VertexArray v_arr2;

			Assert::AreEqual(1, v_arr1.getOpenglName());
			Assert::AreEqual(2, v_arr2.getOpenglName());
		}

		TEST_METHOD(testSetAndGetLabel)
		{
			VertexArray v_arr("CharacterModel");

			Assert::AreEqual("CharacterModel", v_arr.getLabel());
			v_arr.setLabel("PlayerModel");
			Assert::AreEqual("PlayerModel", v_arr.getLabel());
		}

		TEST_METHOD(testCreateAndGetAttribute)
		{
			VertexArray v_arr;
			
			v_arr.createAttribute("Positions", 
				3, 
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			VertexArray::VertexAttribute expected { "Positions", 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0) };
			VertexArray::VertexAttribute actual = v_arr.getAttribute("Positions");
			
			Assert::AreEqual(expected.name, actual.name);
			Assert::AreEqual(expected.index, actual.index);
			Assert::AreEqual(expected.type, actual.type);
			Assert::AreEqual(expected.normalized, actual.normalized);
			Assert::AreEqual(expected.stride, actual.stride);
			Assert::AreSame(expected.offset, actual.offset);

			v_arr.createAttribute("Colors",
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(float) * 3,
				(void*)(sizeof(float) * 3));

			expected = { "Colors", 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 3) };
			actual = v_arr.getAttribute(1);

			Assert::AreEqual(expected.name, actual.name);
			Assert::AreEqual(expected.index, actual.index);
			Assert::AreEqual(expected.type, actual.type);
			Assert::AreEqual(expected.normalized, actual.normalized);
			Assert::AreEqual(expected.stride, actual.stride);
			Assert::AreSame(expected.offset, actual.offset);
		}

		TEST_METHOD(testSetAttributeName)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeName("Positions", "Pos");
			Assert::AreEqual("Pos", v_arr.vertex_attributes.at(0).name.c_str());

			v_arr.setAttributeName(0, "Positions");
			Assert::AreEqual("Positions", v_arr.vertex_attributes.at(0).name.c_str());
		}

		TEST_METHOD(testSetAttributeSize)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeSize("Positions", 4);
			Assert::AreEqual(4, v_arr.vertex_attributes.at(0).size);
			GLint size;
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			Assert::AreEqual(size, v_arr.vertex_attributes.at(0).size);

			v_arr.setAttributeSize(0, 3);
			Assert::AreEqual(3, v_arr.vertex_attributes.at(0).size);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			Assert::AreEqual(size, v_arr.vertex_attributes.at(0).size);
		}

		TEST_METHOD(testSetAttributeNormalized)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeNormalized("Positions", true);
			Assert::AreEqual((GLboolean)GL_TRUE, v_arr.vertex_attributes.at(0).normalized);
			GLint normalized;
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			Assert::AreEqual((GLboolean)normalized, v_arr.vertex_attributes.at(0).normalized);

			v_arr.setAttributeNormalized(0, false);
			Assert::AreEqual((GLboolean)GL_FALSE, v_arr.vertex_attributes.at(0).normalized);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			Assert::AreEqual((GLboolean)normalized, v_arr.vertex_attributes.at(0).normalized)
		}

		TEST_METHOD(testSetAttributeType)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeType("Positions", GL_INT);
			Assert::AreEqual((GLenum)GL_INT, v_arr.vertex_attributes.at(0).type);
			GLint type;
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			Assert::AreEqual((GLenum)type, v_arr.vertex_attributes.at(0).type);

			v_arr.setAttributeNormalized(0, GL_FLOAT);
			Assert::AreEqual((GLenum)GL_FLOAT, v_arr.vertex_attributes.at(0).type);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			Assert::AreEqual((GLenum)type, v_arr.vertex_attributes.at(0).type);
		}

		TEST_METHOD(testSetAttributeOffset)
		{

		}

		TEST_METHOD(testSetAttributeStride)
		{

		}
	};
}