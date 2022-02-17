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
	public:

		TEST_CLASS_INITIALIZE(InitApplication)
		{
			glfwInit();

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

			//Create windows
			GLFWwindow* window = glfwCreateWindow(800, 640, "Test", NULL, NULL);

			if (window == nullptr) {
				std::cout << "Failed to create window" << std::endl;
			}

			glfwMakeContextCurrent(window);

			//Get opengl functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}

			glViewport(0, 0, 800, 640);
		}

		TEST_CLASS_CLEANUP(DestroyApplication)
		{
			glfwTerminate();
		}

		TEST_METHOD(testDefaultConstructor)
		{
			VertexArray v_arr;
			//Ensure the vertex array was created and bound
			Assert::IsTrue(glIsVertexArray(v_arr.opengl_name));
			//There should be no vertex attributes in the VAO
			Assert::AreEqual(0, (int)v_arr.vertex_attributes.size());
			Assert::AreEqual(0, (int)v_arr.attribute_names.size());

			//Was the opengl name set properly?
			Assert::AreEqual((GLuint)1, v_arr.getOpenglName());
			Assert::AreEqual("1", v_arr.getLabel().c_str());

			GLchar* label = new GLchar[v_arr.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.getOpenglName(),
				v_arr.getLabel().size() + 1,
				NULL,
				label);
			Assert::AreEqual(label, v_arr.getLabel().c_str());
			delete[] label;
		}

		TEST_METHOD(testCopyConstructor)
		{
			VertexArray v_arr1;

			//Init some dummy data to make opengl happy.
			GLuint buffer;
			glCreateBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			float data[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			glNamedBufferStorage(buffer, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);

			v_arr1.createAttribute("Positions", 0, 4, GL_FLOAT, false, 0, (void*)(0));
			v_arr1.createAttribute("Color", 1, 3, GL_FLOAT, false, sizeof(float)*7, (void*)(sizeof(float)*4));
			v_arr1.createAttribute("UV", 2, 3, GL_FLOAT, false, sizeof(float)*7, (void*)(sizeof(float)*7));
			VertexArray v_arr2 = v_arr1;

			//Test if the two objects were created and bound.
			Assert::IsTrue(glIsVertexArray(v_arr1.opengl_name));
			Assert::IsTrue(glIsVertexArray(v_arr2.opengl_name));

			//The two objects should have the same attributes.
			Assert::AreEqual(v_arr1.vertex_attributes.size(), v_arr2.vertex_attributes.size());
			Assert::AreEqual(v_arr1.attribute_names.size(), v_arr2.attribute_names.size());

			//Those attributes should also have the same values
			auto it1 = v_arr1.vertex_attributes.begin();
			auto it2 = v_arr2.vertex_attributes.begin();
			for (; it1 != v_arr1.vertex_attributes.end() && 
				it2 != v_arr2.vertex_attributes.end(); 
				it1++, it2++)
			{
				VertexArray::VertexAttribute attrb1 = it1->second;
				VertexArray::VertexAttribute attrb2 = it2->second;
				Assert::AreEqual(attrb1.name, attrb2.name);
				Assert::AreEqual(attrb1.index, attrb2.index);
				Assert::AreEqual(attrb1.normalized, attrb2.normalized);
				Assert::AreEqual(attrb1.type, attrb2.type);
				Assert::AreEqual(attrb1.size, attrb2.size);
				Assert::AreEqual(attrb1.offset, attrb2.offset);
				Assert::AreEqual(attrb1.stride, attrb2.stride);
			}

			//Test if the vertex attribute propeties are set in the context.
			v_arr2.bind();
			for (auto a : v_arr2.vertex_attributes)
			{
				auto attrib = a.second;
				GLint size;
				GLint type;
				GLint normalized;
				GLint stride;
				void* offset;
				GLint enabled;

				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
				glGetVertexAttribPointerv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

				Assert::AreEqual(attrib.size, size);
				Assert::AreEqual((GLint)attrib.type, type);
				Assert::AreEqual((GLint)attrib.normalized, normalized);
				Assert::AreEqual((GLint)attrib.stride, stride);
				Assert::AreEqual(attrib.offset, offset);
				Assert::AreEqual((GLint)attrib.enabled, enabled);//They both should be false
				Assert::IsFalse(attrib.enabled);
				Assert::IsFalse(enabled);
			}
			v_arr2.unbind();

			//Test to make sure both objects contain the same attribute names and indexes
			auto attrib_id1 = v_arr1.attribute_names.begin();
			auto attrib_id2 = v_arr2.attribute_names.begin();
			for (; attrib_id1 != v_arr1.attribute_names.end() && 
				attrib_id2 != v_arr2.attribute_names.end(); 
				attrib_id1++, attrib_id2++)
			{
				auto name1 = attrib_id1->first;
				auto name2 = attrib_id2->first;
				auto index1 = attrib_id1->second;
				auto index2 = attrib_id2->second;

				Assert::AreEqual(name1, name2);
				Assert::AreEqual(index1, index2);
			}

			//They should NOT have the same opengl names or labels
			Assert::AreNotEqual(v_arr1.getOpenglName(), v_arr2.getOpenglName());
			Assert::AreNotEqual(v_arr1.getLabel(), v_arr2.getLabel());

			//Make sure the object lables for both objects are properly set
			GLchar* vao1_label = new GLchar[v_arr1.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr1.opengl_name,
				v_arr1.label.size() + 1,
				NULL,
				vao1_label);
			Assert::AreEqual(vao1_label, v_arr1.getLabel().c_str());
			delete[] vao1_label;

			GLchar* vao2_label = new GLchar[v_arr2.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr2.getOpenglName(),
				v_arr2.getLabel().size() + 1,
				NULL,
				vao2_label);
			Assert::AreEqual(vao2_label, v_arr2.getLabel().c_str());
			delete[] vao2_label;
		}

		TEST_METHOD(testNameConstructor)
		{
			VertexArray v_arr("SoldierModel");

			//Test if the vertex array was created and bound.
			Assert::IsTrue(glIsVertexArray(v_arr.opengl_name));

			//Test if the label was set properly
			Assert::AreEqual("SoldierModel", v_arr.getLabel().c_str());
			GLchar* label = new GLchar[v_arr.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.opengl_name,
				v_arr.label.size() + 1,
				NULL,
				label);
			Assert::AreEqual(label, v_arr.label.c_str());
			delete[] label;

			//There should be no vertex attributes in the VAO
			Assert::AreEqual(0, (int)v_arr.vertex_attributes.size());
			Assert::AreEqual(0, (int)v_arr.attribute_names.size());
			
			//Was the opengl name set properly?
			Assert::AreEqual((GLuint)1, v_arr.getOpenglName());
		}
		
		TEST_METHOD(testInitListConstructor)
		{
			//Init some dummy data to make opengl happy.
			GLuint buffer;
			glCreateBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			float data[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			glNamedBufferStorage(buffer, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);

			VertexArray v_arr {
				{ "Positions", 0, 3, GL_FLOAT, false, 0, (void*)(0) },
				{ "Color", 1, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
				{ "UV", 2, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 7) }
			};

			//Test if the label was set properly.
			GLchar* label = new GLchar[v_arr.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.getOpenglName(),
				v_arr.getLabel().size() + 1,
				NULL,
				label);
			Assert::AreEqual(label, v_arr.getLabel().c_str());
			delete[] label;

			//Test if the vertex array was created and bound
			Assert::IsTrue(glIsVertexArray(v_arr.opengl_name));

			//Test if all vertex attributes have been initialized properly
			Assert::AreEqual("Positions", v_arr.getAttribute("Positions").name.c_str());
			Assert::AreEqual((GLuint)0, v_arr.getAttribute("Positions").index);
			Assert::AreEqual(3, v_arr.getAttribute("Positions").size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute("Positions").type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute("Positions").normalized);
			Assert::AreEqual(0, v_arr.getAttribute("Positions").stride);
			Assert::AreEqual((void*)(0), v_arr.getAttribute("Positions").offset);

			Assert::AreEqual("Color", v_arr.getAttribute("Color").name.c_str());
			Assert::AreEqual((GLuint)1, v_arr.getAttribute("Color").index);
			Assert::AreEqual(3, v_arr.getAttribute("Color").size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute("Color").type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute("Color").normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 7), v_arr.getAttribute("Color").stride);
			Assert::AreEqual((void*)(sizeof(float) * 4), v_arr.getAttribute("Color").offset);

			Assert::AreEqual("UV", v_arr.getAttribute("UV").name.c_str());
			Assert::AreEqual((GLuint)2, v_arr.getAttribute("UV").index);
			Assert::AreEqual(3, v_arr.getAttribute("UV").size);
			Assert::AreEqual(GL_FLOAT, (int)v_arr.getAttribute("UV").type);
			Assert::AreEqual(false, (bool)v_arr.getAttribute("UV").normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 7), v_arr.getAttribute("UV").stride);
			Assert::AreEqual((void*)(sizeof(float) * 7), v_arr.getAttribute("UV").offset);

			//Test if the names and indexes were stored
			Assert::AreEqual((GLuint)0, v_arr.attribute_names.at("Positions"));
			Assert::AreEqual((GLuint)1, v_arr.attribute_names.at("Color"));
			Assert::AreEqual((GLuint)2, v_arr.attribute_names.at("UV"));

			//Test if the vertex attribute propeties are set in the context.
			v_arr.bind();
			for (auto a : v_arr.vertex_attributes)
			{
				auto attrib = a.second;
				GLint size;
				GLint type;
				GLint normalized;
				GLint stride;
				void* offset;
				GLint enabled;

				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
				glGetVertexAttribPointerv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

				Assert::AreEqual(attrib.size, size);
				Assert::AreEqual((GLint)attrib.type, type);
				Assert::AreEqual((GLint)attrib.normalized, normalized);
				Assert::AreEqual((GLint)attrib.stride, stride);
				Assert::AreEqual(attrib.offset, offset);
				Assert::AreEqual((GLint)attrib.enabled, enabled);//They both should be false
				Assert::IsFalse(attrib.enabled);
				Assert::IsFalse(enabled);
			}
			v_arr.unbind();
		}

		TEST_METHOD(testDestructor)
		{
			GLuint v_name;
			{
				VertexArray v_arr{
					{ "Positions", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) },
					{ "Color", 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
					{ "UV", 2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 7) }
				};

				v_name = v_arr.opengl_name;
				Assert::IsTrue(glIsVertexArray(v_name));
			}
			//Make sure the vertex array object is deleted from the context.
			Assert::IsFalse(glIsVertexArray(v_name));
		}

		TEST_METHOD(testBindAndUnbind)
		{
			VertexArray v_arr1;
			VertexArray v_arr2;
			GLint current;

			v_arr1.bind();
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
			Assert::IsTrue(v_arr1.isBound());
			Assert::AreEqual((GLint)v_arr1.opengl_name, current);
			Assert::IsFalse(v_arr2.isBound());
			Assert::AreNotEqual((GLint)v_arr2.opengl_name, current);
			
			Assert::AreEqual((GLint)VertexArray::current_bound_vao, current); //The two should always match no matter what.
			Assert::AreEqual(v_arr1.opengl_name, VertexArray::current_bound_vao); //Sanity check

			v_arr2.bind();
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
			Assert::IsFalse(v_arr1.isBound());
			Assert::AreNotEqual((GLint)v_arr1.opengl_name, current);
			Assert::IsTrue(v_arr2.isBound());
			Assert::AreEqual((GLint)v_arr2.opengl_name, current);

			Assert::AreEqual((GLint)VertexArray::current_bound_vao, current);
			Assert::AreEqual(v_arr2.opengl_name, VertexArray::current_bound_vao);

			v_arr1.unbind(); //This call should not unbind the currently bound VAO. Essentially, it should do nothing.
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
			Assert::IsTrue(v_arr2.isBound());
			Assert::AreEqual((GLint)v_arr2.opengl_name, current);
			Assert::AreEqual((GLint)VertexArray::current_bound_vao, current);

			v_arr2.unbind();
			Assert::IsFalse(v_arr2.isBound());
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
			Assert::AreEqual(0, current); //Unbiding a bound VAO should set the currently bound vao to 0
			Assert::AreEqual((GLuint)0, VertexArray::current_bound_vao);
		}

		TEST_METHOD(testEnableAndDisableAttribute)
		{
			VertexArray v_arr {
				{ "Positions", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) },
				{ "Color", 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 4) },
				{ "UV", 2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 7) }
			};

			v_arr.enableAttribute("Positions");
			v_arr.enableAttribute("Color");
			v_arr.enableAttribute("UV");

			v_arr.bind();
			for each (auto v in v_arr.vertex_attributes)
			{
				VertexArray::VertexAttribute attrib = v.second;
				GLint state;
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &state);
				Assert::IsTrue(state == GL_TRUE ? true : false);
			}

			v_arr.disableAttribute("Positions");
			v_arr.disableAttribute("Color");
			v_arr.disableAttribute("UV");

			v_arr.bind();
			for each (auto v in v_arr.vertex_attributes)
			{
				VertexArray::VertexAttribute attrib = v.second;
				GLint state;
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &state);
				Assert::IsFalse(state == GL_TRUE ? true : false);
			}
		}

		TEST_METHOD(testSetGenericAttribute)
		{

			//Test with a brace list of values.
			VertexArray::setGenericAttribute(1, { 0.5f, 0.2f, 0.0f });
			VertexArray::setGenericAttribute(0, { 5.0f, 5.0f, 2.0f });

			float actualPos[3];
			float* expectedPos = new float[]{ 5.0f, 5.0f, 2.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actualPos);

			bool same = true;
			for (int i = 0; i < 3; i++)
			{
				if (expectedPos[i] != actualPos[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);

			float actualCol[3];
			float* expectedCol = new float[] { 0.5f, 0.2f, 0.0f };
			glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB, actualCol);

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

			//Test single value init list
			VertexArray::setGenericAttribute(1, { 1.0f });
			VertexArray::setGenericAttribute(0, { 2.0f });

			float* expected = new float[] {1.0f, 0.0f, 0.0f, 0.0f };
			float actual[4];
			glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected[0], actual[0]);
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			expected[0] = 2.0f;
			Assert::AreEqual(expected[0], actual[0]);
			delete[] expected;

			//Test two value init list
			VertexArray::setGenericAttribute(1, { 1.0f, 0.5f });
			VertexArray::setGenericAttribute(0, { 2.0f, 3.0f });

			float* expected2 = new float[] {1.0f, 0.5f};
			glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB, actual);
			same = true;
			for (int i = 0; i < 2; i++)
			{
				if (expected2[i] != actual[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			expected2[0] = 2.0f; expected2[1] = 3.0f;
			same = true;
			for (int i = 0; i < 2; i++)
			{
				if (expected2[i] != actual[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);
			delete[] expected2;

			//Test 4 value init list
			VertexArray::setGenericAttribute(1, { 2.0f, 1.0f, 1.3f, 1.0f });
			VertexArray::setGenericAttribute(0, { 1.0f, 4.0f, 3.0f, 1.0f });

			float* expected4 = new float[] { 2.0f, 1.0f, 1.3f, 1.0f };
			glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB, actual);
			same = true;
			for (int i = 0; i < 4; i++)
			{
				if (expected4[i] != actual[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			expected4[0] = 1.0f; expected4[1] = 4.0f; expected4[2] = 3.0f, expected4[3] = 1.0f;
			same = true;
			for (int i = 0; i < 4; i++)
			{
				if (expected4[i] != actual[i]) {
					same = false;
					break;
				}
			}
			Assert::IsTrue(same);
			delete[] expected4;

			//Test 1 value array
			float pos1[1] = { 4.0f };
			VertexArray::setGenericAttribute(0, pos1);

			float* expected_arr1 = new float[] {4.0f};
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_arr1[0], actual[0]);
			delete[] expected_arr1;

			//Test 2 value array
			float pos2[2] = { 3.0f, 5.0f };
			VertexArray::setGenericAttribute(0, pos2);

			float* expected_arr2 = new float[] { 3.0f, 5.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_arr2[0], actual[0]);
			Assert::AreEqual(expected_arr2[1], actual[1]);
			delete[] expected_arr2;

			//Test 3 value array
			float pos3[3] = { 1.0f, 6.0f, 2.0f };
			VertexArray::setGenericAttribute(0, pos3);

			float* expected_arr3 = new float[] { 1.0f, 6.0f, 2.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_arr3[0], actual[0]);
			Assert::AreEqual(expected_arr3[1], actual[1]);
			Assert::AreEqual(expected_arr3[2], actual[2]);
			delete[] expected_arr3;

			//Test 4 value array
			float pos4[4] = { 1.0f, 5.0f, 3.0f, 1.0f };
			VertexArray::setGenericAttribute(0, pos4);

			float* expected_arr4 = new float[] { 1.0f, 5.0f, 3.0f, 1.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_arr4[0], actual[0]);
			Assert::AreEqual(expected_arr4[1], actual[1]);
			Assert::AreEqual(expected_arr4[2], actual[2]);
			Assert::AreEqual(expected_arr4[3], actual[3]);
			delete[] expected_arr4;

			//Test single float scalar value
			VertexArray::setGenericAttribute(0, 4.0f);
			float* expected_floatscalar = new float[] { 4.0f, 4.0f, 4.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_floatscalar[0], actual[0]);
			Assert::AreEqual(expected_floatscalar[1], actual[1]);
			Assert::AreEqual(expected_floatscalar[2], actual[2]);
			delete[] expected_floatscalar;

			//Test single integer scalar value
			VertexArray::setGenericAttribute(0, 3);
			float* expected_intscalar = new float[] { 3.0f, 3.0f, 3.0f };
			glGetVertexAttribfv(0, GL_CURRENT_VERTEX_ATTRIB, actual);
			Assert::AreEqual(expected_intscalar[0], actual[0]);
			Assert::AreEqual(expected_intscalar[1], actual[1]);
			Assert::AreEqual(expected_intscalar[2], actual[2]);
			delete[] expected_intscalar;
		}

		TEST_METHOD(testGetOpenglName)
		{
			VertexArray v_arr1;
			VertexArray v_arr2;

			Assert::AreEqual((GLuint)1, v_arr1.getOpenglName());
			Assert::AreEqual((GLuint)2, v_arr2.getOpenglName());

			//Test if the returned name matches what is stored in the context.
			Assert::IsTrue(glIsVertexArray(v_arr1.getOpenglName()));
			Assert::IsTrue(glIsVertexArray(v_arr2.getOpenglName()));
		}

		TEST_METHOD(testSetAndGetLabel)
		{
			VertexArray v_arr("CharacterModel");

			//Test if label is set properly
			Assert::AreEqual("CharacterModel", v_arr.getLabel().c_str());
			v_arr.setLabel("PlayerModel");
			Assert::AreEqual("PlayerModel", v_arr.getLabel().c_str());

			//Test if label is stored in the context.
			GLchar* label = new GLchar[v_arr.getLabel().size() + 1];
			glGetObjectLabel(GL_VERTEX_ARRAY,
				v_arr.getOpenglName(),
				v_arr.getLabel().size() + 1,
				NULL,
				label);
			Assert::AreEqual(label, v_arr.getLabel().c_str());
			delete[] label;
		}

		TEST_METHOD(testCreateAndGetAttribute)
		{
			VertexArray v_arr;

			//Init some dummy data to make opengl happy.
			GLuint buffer;
			glCreateBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			float data[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			glNamedBufferStorage(buffer, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);
			
			v_arr.createAttribute("Positions",
				0,
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
			Assert::AreEqual(expected.offset, actual.offset);

			v_arr.createAttribute("Colors",
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(float) * 3,
				(void*)(sizeof(float) * 3));

			expected = { "Colors", 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 3) };
			actual = v_arr.getAttribute("Colors");

			Assert::AreEqual(expected.name, actual.name);
			Assert::AreEqual(expected.index, actual.index);
			Assert::AreEqual(expected.type, actual.type);
			Assert::AreEqual(expected.normalized, actual.normalized);
			Assert::AreEqual(expected.stride, actual.stride);
			Assert::AreEqual(expected.offset, actual.offset);

			//Test if the vertex attribute properties are set in the context.
			v_arr.bind();
			for (auto a : v_arr.vertex_attributes)
			{
				auto attrib = a.second;
				GLint size;
				GLint type;
				GLint normalized;
				GLint stride;
				void* offset;
				GLint enabled;

				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
				glGetVertexAttribPointerv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

				Assert::AreEqual(attrib.size, size);
				Assert::AreEqual((GLint)attrib.type, type);
				Assert::AreEqual((GLint)attrib.normalized, normalized);
				Assert::AreEqual((GLint)attrib.stride, stride);
				Assert::AreEqual(attrib.offset, offset);
				Assert::AreEqual((GLint)attrib.enabled, enabled);//They both should be false
				Assert::IsFalse(attrib.enabled);
				Assert::IsFalse(enabled);
			}
			v_arr.unbind();

			//Test to make sure the correct attribute names are stored
			Assert::IsTrue(v_arr.attribute_names.count("Positions"));
			Assert::IsTrue(v_arr.attribute_names.count("Colors"));
		}

		TEST_METHOD(testSetAttributeName)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			//Test if name is set properly
			v_arr.setAttributeName("Positions", "Pos");
			auto it = v_arr.attribute_names.find("Positions");
			auto not_found = v_arr.attribute_names.end();
			Assert::IsTrue(it == not_found ? true : false);
			it = v_arr.attribute_names.find("Pos");
			Assert::IsFalse(it == not_found ? true : false);
			Assert::AreEqual("Pos", v_arr.vertex_attributes.at(0).name.c_str());

			v_arr.setAttributeName("Pos", "Positions");
			it = v_arr.attribute_names.find("Positions");
			not_found = v_arr.attribute_names.end();
			Assert::IsFalse(it == not_found ? true : false);
			it = v_arr.attribute_names.find("Pos");
			Assert::IsTrue(it == not_found ? true : false);
			Assert::AreEqual("Positions", v_arr.vertex_attributes.at(0).name.c_str());
		}

		TEST_METHOD(testSetAttributeSize)
		{

			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeSize("Positions", 4);
			Assert::AreEqual(4, v_arr.vertex_attributes.at(0).size);
			GLint size;
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			Assert::AreEqual(size, v_arr.vertex_attributes.at(0).size);

			v_arr.setAttributeSize("Positions", 3);
			Assert::AreEqual(3, v_arr.vertex_attributes.at(0).size);
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			Assert::AreEqual(size, v_arr.vertex_attributes.at(0).size);

			//Make sure the rest of the attributes are the same.
			v_arr.bind();
			GLint type;
			void* offset;
			GLint normalized;
			GLint stride;
			GLint enabled;

			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribPointerv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);

			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual((void*)(0), offset);
			Assert::AreEqual(0, stride);
			Assert::IsFalse(enabled);
			v_arr.unbind();
		}

		TEST_METHOD(testSetAttributeNormalized)
		{

			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));


			v_arr.setAttributeNormalized("Positions", true);
			Assert::AreEqual((GLboolean)GL_TRUE, v_arr.vertex_attributes.at(0).normalized);
			GLint normalized;
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			Assert::AreEqual((GLboolean)normalized, v_arr.vertex_attributes.at(0).normalized);

			v_arr.setAttributeNormalized("Positions", false);
			Assert::AreEqual((GLboolean)GL_FALSE, v_arr.vertex_attributes.at(0).normalized);
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			Assert::AreEqual((GLboolean)normalized, v_arr.vertex_attributes.at(0).normalized);

			//Make sure the rest of the attributes are the same.
			v_arr.bind();
			GLint size;
			GLint type;
			void* offset;
			GLint stride;
			GLint enabled;

			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribPointerv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual((void*)(0), offset);
			Assert::AreEqual(0, stride);
			Assert::IsFalse(enabled);
			v_arr.unbind();
		}

		TEST_METHOD(testSetAttributeType)
		{
			////Init some dummy data to make opengl happy.
			//GLuint buffer;
			//glCreateBuffers(1, &buffer);
			//glBindBuffer(GL_ARRAY_BUFFER, buffer);
			//float data[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			//glNamedBufferStorage(buffer, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);

			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeType("Positions", GL_INT);
			Assert::AreEqual((GLenum)GL_INT, v_arr.vertex_attributes.at(0).type);
			GLint type;
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			Assert::AreEqual((GLenum)type, v_arr.vertex_attributes.at(0).type);

			v_arr.setAttributeType("Positions", GL_FLOAT);
			Assert::AreEqual((GLenum)GL_FLOAT, v_arr.vertex_attributes.at(0).type);
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			Assert::AreEqual((GLenum)type, v_arr.vertex_attributes.at(0).type);

			//Make sure the rest of the attributes are the same.
			v_arr.bind();
			GLint size;
			GLint stride;
			void* offset;
			GLint normalized;
			GLint enabled;

			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribPointerv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);

			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual((void*)(0), offset);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(3, size);
			Assert::IsFalse(enabled);
			v_arr.unbind();
		}

		TEST_METHOD(testSetAttributeOffset)
		{
			//Init some dummy data to make opengl happy.
			GLuint buffer;
			glCreateBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			float data[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			glNamedBufferStorage(buffer, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);

			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeOffset("Positions", (void*)(sizeof(float) * 3));
			Assert::AreEqual((void*)(sizeof(float) * 3), v_arr.vertex_attributes.at(0).offset);
			void* offset;
			v_arr.bind();
			glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			Assert::AreEqual(offset, v_arr.vertex_attributes.at(0).offset);

			v_arr.setAttributeOffset("Positions", 0);
			Assert::AreEqual((void*)(0), v_arr.vertex_attributes.at(0).offset);
			v_arr.bind();
			glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			Assert::AreEqual(offset, v_arr.vertex_attributes.at(0).offset);

			//Make sure the rest of the attributes are the same.
			v_arr.bind();
			GLint size;
			GLint type;
			GLint normalized;
			GLint stride;
			GLint enabled;

			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::IsFalse(enabled);
			v_arr.unbind();
		}

		TEST_METHOD(testSetAttributeStride)
		{
			VertexArray v_arr;
			v_arr.createAttribute("Positions",
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)(0));

			v_arr.setAttributeStride("Positions", sizeof(float) * 3);
			Assert::AreEqual((GLsizei)(sizeof(float) * 3), v_arr.vertex_attributes.at(0).stride);
			GLint stride;
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			Assert::AreEqual(stride, v_arr.vertex_attributes.at(0).stride);

			v_arr.setAttributeStride("Positions", 0);
			Assert::AreEqual(0, v_arr.vertex_attributes.at(0).stride);
			v_arr.bind();
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			Assert::AreEqual(stride, v_arr.vertex_attributes.at(0).stride);

			//Make sure the rest of the attributes are the same.
			v_arr.bind();
			GLint size;
			GLint type;
			void* offset;
			GLint normalized;
			GLint enabled;

			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribPointerv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
			glGetVertexAttribiv(v_arr.vertex_attributes.at(0).index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);

			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual((void*)(0), offset);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(3, size);
			Assert::IsFalse(enabled);
			v_arr.unbind();
		}

		TEST_METHOD(testAddAttribute)
		{
			VertexArray v_arr;
			v_arr.addAttributes({
				{ "Pos", 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0 },
				{ "Color", 1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 3) }
				});

			//Test if the attributes were added
			Assert::AreEqual(2, (int)v_arr.vertex_attributes.size());

			Assert::AreEqual("Pos", v_arr.vertex_attributes.at(0).name.c_str());
			Assert::AreEqual((GLuint)0, v_arr.vertex_attributes.at(0).index);
			Assert::AreEqual(3, v_arr.vertex_attributes.at(0).size);
			Assert::AreEqual((GLenum)GL_FLOAT, v_arr.vertex_attributes.at(0).type);
			Assert::AreEqual((GLboolean)GL_FALSE, v_arr.vertex_attributes.at(0).normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 3), v_arr.vertex_attributes.at(0).stride);
			Assert::AreEqual((void*)0, v_arr.vertex_attributes.at(0).offset);
			Assert::AreEqual(false, v_arr.vertex_attributes.at(0).enabled);

			Assert::AreEqual("Color", v_arr.vertex_attributes.at(1).name.c_str());
			Assert::AreEqual((GLuint)1, v_arr.vertex_attributes.at(1).index);
			Assert::AreEqual(4, v_arr.vertex_attributes.at(1).size);
			Assert::AreEqual((GLenum)GL_FLOAT, v_arr.vertex_attributes.at(1).type);
			Assert::AreEqual((GLboolean)GL_FALSE, v_arr.vertex_attributes.at(1).normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 3), v_arr.vertex_attributes.at(1).stride);
			Assert::AreEqual((void*)(sizeof(float) * 3), v_arr.vertex_attributes.at(1).offset);
			Assert::AreEqual(false, v_arr.vertex_attributes.at(1).enabled);

			//Test if names were stored
			Assert::AreEqual((GLuint)0, v_arr.attribute_names.at("Pos"));
			Assert::AreEqual((GLuint)1, v_arr.attribute_names.at("Color"));

			//Test if the attributes were set in the context
			for (auto a : v_arr.vertex_attributes)
			{
				auto attrib = a.second;
				GLint size;
				GLint type;
				GLint normalized;
				GLint stride;
				void* offset;
				GLint enabled;

				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
				glGetVertexAttribPointerv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
				glGetVertexAttribiv(attrib.index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

				Assert::AreEqual(attrib.size, size);
				Assert::AreEqual((GLint)attrib.type, type);
				Assert::AreEqual((GLint)attrib.normalized, normalized);
				Assert::AreEqual((GLint)attrib.stride, stride);
				Assert::AreEqual(attrib.offset, offset);
				Assert::AreEqual((GLint)attrib.enabled, enabled);//They both should be false
				Assert::IsFalse(attrib.enabled);
				Assert::IsFalse(enabled);
			}

			//Test if attributes are replaced when adding one with an index that already exists
			VertexArray::VertexAttribute new_attrib { 
				"UV", 
				1, 
				2, 
				GL_FLOAT, 
				GL_FALSE, 
				sizeof(float) * 3, 
				(void*)(sizeof(float) * 5)
			};

			v_arr.addAttributes(new_attrib);

			Assert::AreEqual("UV", v_arr.vertex_attributes.at(1).name.c_str());
			Assert::AreEqual((GLuint)1, v_arr.vertex_attributes.at(1).index);
			Assert::AreEqual(2, v_arr.vertex_attributes.at(1).size);
			Assert::AreEqual((GLenum)GL_FLOAT, v_arr.vertex_attributes.at(1).type);
			Assert::AreEqual((GLboolean)GL_FALSE, v_arr.vertex_attributes.at(1).normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 3), v_arr.vertex_attributes.at(1).stride);
			Assert::AreEqual((void*)(sizeof(float) * 5), v_arr.vertex_attributes.at(1).offset);
			Assert::AreEqual(false, v_arr.vertex_attributes.at(1).enabled);

			//Test if it was set in the context
			v_arr.bind();
			GLint size;
			GLint type;
			GLint normalized;
			GLint stride;
			void* offset;
			GLint enabled;

			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

			Assert::AreEqual(2, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual((GLsizei)(sizeof(float) * 3), stride);
			Assert::AreEqual((void*)(sizeof(float) * 5), offset);
			Assert::AreEqual(GL_FALSE, enabled);//They both should be false
			Assert::IsFalse(enabled);
		}
	};
}