#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BenchmarkTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(MapSizeFactor)
		{

			Assert::AreEqual(1,1,L"Passed");
		}
		TEST_METHOD(DriverCountFactor)
		{
			Assert::AreEqual(1,1,L"Passed");
		}

	};
}