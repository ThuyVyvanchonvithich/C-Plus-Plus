#include <iostream>
#include <fstream>

using namespace std;
#define FILE_PATH "data.txt"

int main()
{
	int *arr = new int[30] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111, 121, 131, 141, 151,
		161, 171, 181, 191, 202};
	
	ifstream fileIn;
	ofstream fileOut;

	//write data to file
	fileOut.open(FILE_PATH, ios::trunc);

	for (int i = 0; i < 20; i++)
	{
		fileOut << arr[i] << endl;
	}

	fileOut.close();


	//read data from file
	fileIn.open(FILE_PATH);

	for (int i = 0; i < 20; i++) {
		fileIn >> arr[i];
	}

	fileIn.close();

	for (int i = 0; i < 20; i++) {
		if (arr[i] & 1) {
			cout << arr[i] << endl;
		}
	}

	return 0;
}

