#include "pch.h"
#include "CppUnitTest.h"
#include "../пр7.3рек/7.3рек.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73рек
{
	TEST_CLASS(UnitTest73рек)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int count = 0;
			int colCount = 2;
			int rowCount = 2;
			bool result = 0;
			int** a = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				a[i] = new int[colCount];
			a[0][0] = -1;
			a[1][1] = -4;
			a[0][1] = 12;
			a[1][0] = 0;
			Part1_CountCols(a, rowCount, colCount, count, result, 0);
			Assert::AreEqual(1, count);
		}
	};
}
