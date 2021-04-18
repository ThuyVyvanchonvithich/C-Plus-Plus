#include "car.h"
#include "MyUtils.h"

/** Main Function */
int main()
{
	int arr[LENGTH] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int arr2[3] = { 20, 40, 60 };
	Car car(arr, arr2);

	//Car *car = new Car();

	//define alter name for CarDrive
	CarDrive carDrive;
	//define alter name for CompareAlgorithm
	CompareAlgorithm cmp;

	ifstream file_in;
	ofstream file_out;

	

	//declare default password
	bool isNumber = true;
	bool isExist = false;
	int arr_velocity[3];
	int defaultPassword[8];
	int arr_password[8];
	carDrive.speed = 0;

	//Read data from file binary
	file_in.open(FILE_PATH, ios::in | ios::binary);
	file_in.read((char *)&car, sizeof(Car));

	//check file is exist or not
	isExist = isFileExist(file_in);
	
	//Close file after work with file
	file_in.close();

	//Handle login
	car = loginHandler(car, isExist);

	//Clear screen
	system("cls");

	//Handle set safe distance
	car = distanceHandler(car, isExist);
	
	//Write data to file binary
	file_out.open(FILE_PATH, ios::out | ios::binary | ios::trunc);

	file_out.write((char *)&car, sizeof(Car));

	//close file after works with file
	
	file_out.close();
	system("cls");

	//Handle menu gearbox
	menuHandler(car);
	//Power off
	powerOff();

	//system("pause");
	return 0;
}