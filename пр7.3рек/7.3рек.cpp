#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < colCount - 1)
		PrintRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
	PrintRow(a, rowNo, colCount, 0);
	if (rowNo < rowCount - 1)
		PrintRows(a, rowCount, colCount, rowNo + 1);
	else
		cout << endl;
}
void CreateRow(int** a, const int rowNo, const int colCount,
	const int Low, const int High, int colNo)
{
	a[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < colCount - 1)
		CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}
void CreateRows(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int rowNo)
{
	CreateRow(a, rowNo, colCount, Low, High, 0);
	if (rowNo < rowCount - 1)
		CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}
void Part1_ZeroCol(int** a, const int colCount, bool& result,
	int colNo, int rowNo, int& k_zero)
{
	if (a[rowNo][colNo] == 0)
	{
		result = true;
		k_zero++;
	}
	else
		if (colNo < colCount - 1)
			Part1_ZeroCol(a, colCount, result, colNo+1, rowNo , k_zero);
}
void Part1_CountCol(int** a, const int colCount, int& count, int colNo, int rowNo)
{
	if (a[rowNo][colNo] < 0)
		count++;
	if (colNo < colCount - 1)
		Part1_CountCol(a, colCount, count, colNo+1, rowNo);
}
void Part1_CountCols(int** a, const int rowCount, const int colCount,
	int& count, bool& result, int rowNo)
{
	int k_zero = 0;
	Part1_ZeroCol(a, colCount, result, 0, rowNo, k_zero);
	if (k_zero > 0)
		Part1_CountCol(a, colCount, count, 0, rowNo);
	if (rowNo < rowCount - 1)
		Part1_CountCols(a, rowCount, colCount, count, result, rowNo + 1);
}

bool IsMinInRowN(int** a, int rowNo, int value, int colNo, int COLS) {
	if (colNo < COLS) {
		if (a[rowNo][colNo] < value) {
			return false;
		}
		return IsMinInRowN(a, rowNo, value, colNo + 1, COLS);
	}
	return true;
}

bool IsMaxInColK(int** a, int colNo, int value, int rowNo, int ROWS) {
	if (rowNo < ROWS) {
		if (a[rowNo][colNo] > value) {
			return false;
		}
		return IsMaxInColK(a, colNo, value, rowNo + 1, ROWS);
	}
	return true;
}

void FindSaddlePoints(int** a, int rowNo, int colNo, int ROWS, int COLS, int No) {
	if (rowNo < ROWS) {
		if (IsMinInRowN(a, rowNo, a[rowNo][colNo], 0, COLS) &&
			IsMaxInColK(a, colNo, a[rowNo][colNo], 0, ROWS)) {
			cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
		}
		if (colNo < COLS - 1) {
			FindSaddlePoints(a, rowNo, colNo + 1, ROWS, COLS, No);
		}
		else {
			FindSaddlePoints(a, rowNo + 1, 0, ROWS, COLS, No);
		}
	}
}


int main()
{
	srand((unsigned)time(NULL));
	int Low = -7;
	int High = 7;
	int rowCount, colCount;
	cout << "rowCount = "; cin >> rowCount;
	cout << "colCount = "; cin >> colCount;
	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];
	
	 CreateRows(a, rowCount, colCount, Low, High, 0);
	PrintRows(a, rowCount, colCount, 0);
	int count = 0;
	bool result = false;
	Part1_CountCols(a, rowCount, colCount, count, result, 0);
	if (result)
		cout << "count = " << count << endl;
	else
		cout << "there are no zero elements" << endl;
	cout << endl;
	cout << "Saddle points: max in row & min in col" << endl;
	cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
	int No = 0;
	FindSaddlePoints(a, 0, 0, rowCount, colCount, No);
	cout << endl;
	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}