#include "car.h"

/** Main Function */
int main()
{
	//define alter name for CarDrive
	CarDrive car;
	//define alter name for CompareAlgorithm
	CompareAlgorithm cmp;

	//declare default password
	int arr_defaultPassword[LENGTH]{ 8, 5, 2, 1, 3, 6, 4, 7 };
	int arr_password[8];
	car.speed = 0;

	//Require user input the password
	*arr_password = inputPassword(arr_password);
	//sort and show result login
	resultLogin(arr_defaultPassword, arr_password);
	//Clear screen
	system("cls");

	/* DISTANCE*/
	distanceHandler();
	system("cls");

	//Handle menu gearbox
	menuHandler();
	//Power off
	powerOff();

	//system("pause");
	return 0;
}