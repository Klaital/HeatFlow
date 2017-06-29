#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibHeatFlow
{		
	TEST_CLASS(UnitTestProjectConfig)
	{
	public:
		
		TEST_METHOD(TestProjectConfigSetup)
		{
			ProjectConfig *project_config;
			project_config = new ProjectConfig();

			Assert::AreEqual((size_t)0, project_config->get_matrix_size()[0]);
			Assert::AreEqual((size_t)0, project_config->get_matrix_size()[1]);

			project_config->set_title("Hello, world!");
			Assert::AreEqual("Hello, world!", project_config->get_title().c_str());
		}

	};
}
