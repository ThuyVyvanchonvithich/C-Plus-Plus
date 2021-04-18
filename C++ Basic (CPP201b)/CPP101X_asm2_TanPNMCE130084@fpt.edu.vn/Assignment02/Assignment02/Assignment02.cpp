#include "stdafx.h"
#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <regex>

using namespace std;
using namespace std::chrono;

//Define length of array
#define LENGTH 8

/**
* define the global variables for car used in file
*/
typedef struct CarDrive
{
	int arr_defaultPassword[LENGTH]{ 8, 5, 2, 1, 3, 6, 4, 7 };   //The variable saves the user-entered password
	int arr_password[LENGTH];		//The variable saves the user-entered password
	string str_gearChoice;          //The variable saves the user's choice on menu Gearbox
	int gearChoice;                 //The variable saves value cast str_gearChoice variable from string to int
	string str_controlChoice;		//The variable saves the user's choice R or D on menu Gearbox
	int controlChoice;              //The variable saves value cast str_controlChoice variable from string to int
	int speed;                      //The variable saves current speed
	string str_arr_velocity[3];     //The variable save speed of velocity levels that user-entered
	int arr_velocity[LENGTH];		//The variable saves value cast str_arr_velocity variable from string to int
	bool isDrive;                   //The variable saves the state of the Gearbox is D (Drive) mode or not
};
CarDrive car;   //define alter name for CarDrive

/**
* define the global variables for compare algorithm used in file
*/
typedef struct CompareAlgorithm
{
	int count_timesTraversal;		//The variable saves the number of times the algorithm traverses the elements in the array
};
CompareAlgorithm cmp;   //define alter name for CompareAlgorithm

/** Forward declaration for functions used in file */

///A set of algorithm processing functions
void swap(int, int);
void bubbleSort(int arr[LENGTH]);
void selectionSort(int arr[LENGTH], int size);
void printArray(int arr[LENGTH], int size);

///A set of check functions
bool isMatch(int arr1[LENGTH], int arr2[LENGTH]);
bool isDigit(string);
bool isPositiveNumber(int);

///A set of input functions
void inputPassword();
void setVelocityLevel();

///A set of functions that display notification and menus
void displayResultPassword();
void notificationLowerVelocityLv1(bool);
void notificationVelocityLv1ToLv2(bool);
void notificationVelocityLv2ToLv3(bool);
void notificationHigherVelocityLv3(bool);
void displayNotificationVelocityLevel(bool);
void displayNotification();
void gearBoxMenu();
void controlMenu();

void setSpeed();




/** Main Function */
int main()
{

	//declare default password
	int arr_defaultPassword[LENGTH]{ 8, 5, 2, 1, 3, 6, 4, 7 };
	bool isNumber = true;

	//initialize values for the variables
	car.arr_velocity[0] = 0;
	car.arr_velocity[1] = 0;
	car.arr_velocity[2] = 0;
	car.speed = 0;

	//Require user input the password
	inputPassword();

	//Display result password and default password before and after sort
	displayResultPassword();

	//Check whether password and default password after sort are the same or not
	//If not same then give goodbye message and stop program
	if (!isMatch(car.arr_password, car.arr_defaultPassword))
	{

		cout << endl;
		cout << "MA SO CA NHAN KHONG HOP LE!!!" << endl;
		cout << "UNG DUNG DA BI DONG!!!" << endl;

		//Pause screen
		system("pause");
		exit(0);
	}
	else    //if same then pause screen
	{
		//Pause screen
		system("pause");
	}

	//Clear screen
	system("cls");
	setVelocityLevel();
	selectionSort(car.arr_velocity, 3);
	system("cls");


	//Show Gearbox menu
	//Over and over again constantly until user choice POWER OFF
	do
	{
		//system("cls");
		gearBoxMenu();

		//The cases user was chose
		switch (car.gearChoice)
		{
		case 1:     //case 1: P (Park)
					//Clear screen
			system("cls");

			if (car.speed > 0)
			{
				cout << "HAY CHAC CHAN XE DA DUNG VA VAN TOC LA 0 KM/H \n" << endl;
				break;
			}
			else
			{
				cout << "DA VE SO P." << endl;
				cout << "CHU Y SU DUNG PHANH TAY DE DAM BAO AN TOAN \n" << endl;
			}
			break;

		case 2:   //case 2: R (Reverse)
				  //Clear screen
			system("cls");
			//Over and over again constantly until user choice Back to Gearbox menu
			do
			{
				//Check the state of car is D (Drive) mode or not
				//if is D mode then show Warning message
				if (car.isDrive && car.speed > 0)
				{
					//Clear screen
					system("cls");
					//show warning message
					cout << "XE DANG CHAY TIEN TOI\n" << endl;
				}
				else    //If is not D mode then do code below
				{
					//Check the car is changing gears between Reverse and Drive or not
					//If the speed is 0 and dose not is speed up or brake then set speed to 7 Km/h
					if (car.speed == 0 && car.controlChoice != 2 && car.controlChoice != 3)
					{
						car.speed = 7;
						//set state D mode to false
						car.isDrive = false;
						displayNotification();
					}
					else        //car has not been stopped
					{
						//set state D mode to false
						car.isDrive = false;
						//show information about current speed
						displayNotification();
					}

					//show Menu D or R mode
					controlMenu();
					//set speed for car
					setSpeed();
				}
			} while (car.controlChoice != 4);
			break;

		case 3:   //case 3: N (Neutral)
				  //Clear screen
			system("cls");

			//Check speed is 0 Km/h or not
			//if is not 0 Km/h then show warning
			if (car.speed > 0)
			{
				cout << "HAY CHAC CHAN XE DA DUNG VA VAN TOC LA 0 KM/H\n" << endl;
				break;
			}
			else    //case the speed is 0 Km/h
			{
				cout << "DA VE SO N.\n" << endl;
			}
			break;

		case 4:     //case 4: D (Drive)
					//Clear screen
			system("cls");

			//Over and over again constantly until user choice Back to Gearbox menu
			do
			{
				//Check the state of car is R (Reverse) mode or not
				//if is R mode then show Warning message
				if (!car.isDrive && car.speed > 0)
				{
					//Clear screen
					system("cls");
					//show warning message
					cout << "XE DANG CHAY LUI\n" << endl;
				}
				else    //If is not D mode then do code below
				{
					//Check the car is changing gears between Reverse and Drive or not
					//If the speed is 0 and dose not is speed up or brake then set speed to 7 Km/h
					if (car.speed == 0 && car.controlChoice != 3 && car.controlChoice != 2)
					{
						car.speed = 7;
						car.isDrive = true;
						displayNotification();
					}
					else        //car has not been stopped
					{
						//set state D mode to false
						car.isDrive = true;
						//show information about current speed
						displayNotification();
					}

					//show Menu D or R mode
					controlMenu();
					//set speed for car
					setSpeed();
				}
			} while (car.controlChoice != 4);
			break;

		case 5:     //case 5: POWER OFF
					//Clear screen
			system("cls");
			break;

		default:    //Throw warning when user does not choice from 1 to 5
					//Clear screen
			system("cls");
			//show warning message
			cout << "VUI LONG CHON TU 1 DEN 5\n" << endl;
			break;
		}
	} while (car.gearChoice != 5);

	//show goodbye notice
	cout << "*---------------- POWER OFF ---------------*" << endl;
	cout << "*                                          *" << endl;
	cout << "*      CAM ON VI DA SU DUNG PHAN MEM       *" << endl;
	cout << "*                                          *" << endl;
	cout << "********************************************" << endl;

	system("pause");
	return 0;
}



/** All Function used in this file */

/// A set of algorithm processing functions

/**
* Function swap value of two variables
*
*@param value1 - 1st value
*@param value2 - 2nd value
*/
void swap(int *value1, int *value2)
{
	int temp = *value1;
	*value1 = *value2;
	*value2 = temp;
}

/**
* Function to implement bubble sort algorithm
*
* @param arr[] - the array want to sort
*/
void bubbleSort(int arr[])
{
	cmp.count_timesTraversal = 0;
	for (int i = 0; i < LENGTH - 1; i++)
	{
		//Whenever traversing an element, increase var count_timesTraversal by one
		cmp.count_timesTraversal++;

		// Last i elements are already in place
		for (int j = 0; j < LENGTH - i - 1; j++)
		{

			//Whenever traversing an element, increase var count_timesTraversal by one
			cmp.count_timesTraversal++;

			//If the preceding value is greater than the value after, swap them
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/**
* Function to implement selection sort algorithm
*
* @param arr[] - the array want to sort
*/
void selectionSort(int arr[], int size)
{
	int min_index;
	cmp.count_timesTraversal = 0;
	// One by one move boundary of unsorted sub-array
	for (int i = 0; i < size - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_index = i;
		//Whenever traversing an element, increase var count_timesTraversal by one
		cmp.count_timesTraversal++;

		for (int j = i + 1; j < size; j++)
		{

			//Whenever traversing an element, increase var count_timesTraversal by one
			cmp.count_timesTraversal++;

			//If minimum element is greater than current element
			//then set current element to minimum element
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}

		// Swap the found minimum element with the first element
		swap(&arr[min_index], &arr[i]);
	}
}

/**
* Function to print an array
*
* @param arr[] - the array want to display
*/
void printArray(int arr[LENGTH], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}



/// A set of check functions

/**
* Function to check whether 2 arrays are the same or not
*
* @param arr1[] - the first array wants to compare
* @param arr2[] - the second array wants to compare
*/
bool isMatch(int arr1[LENGTH], int arr2[LENGTH])
{
	//loop from 0 to LENGTH
	for (int i = 0; i < LENGTH; i++)
	{
		//if at any index, the values of the 2 arrays are not equal
		//Return false
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}

	//Otherwise, return true
	return true;
}

/**
* Function to check user-entered is a digit or not
*
* @param input - user-entered
*/
bool isDigit(string input)
{
	regex pattern("[0-9]+");

	if (!regex_match(input, pattern))
	{
		return false;
	}
	return true;
}

/**
* Function to check user-entered is a positive number or not
*
* @param number - the user-entered number
*/
bool isPositiveNumber(int number)
{
	if (number >= 0)
		return true;
	else
		return false;
}



///A set of input functions

/**
* Function to require user input the password
*/
void inputPassword()
{
	//The variable saves the state of program
	//is the first time show run or not
	bool isFirstTime = true;
	do
	{
		try
		{
			//Reset the failed state
			cin.clear();

			//If does not the first time run program then clear screen
			//Cleans cache when user press Enter or enough 256 characters
			if (!isFirstTime)
			{
				cin.ignore(256, '\n');
			}

			//If is the first time run program then set variable to False
			isFirstTime = false;

			//Require user enter the password
			cout << "NHAP MA SO CA NHAN, MANG 08 SO" << endl;
			for (int i = 0; i < LENGTH; i++)
			{
				cout << "SO THU " << i + 1 << ": ";
				cin >> car.arr_password[i];

				if (cin.fail())
				{
					throw "MA SO CA NHAN CHI CHAP NHAN KY TU LA SO, VUI LONG NHAP LAI";
				}
			}
		}
		catch (const char* msg)
		{
			system("cls");
			cerr << msg << endl;
		}
	} while (cin.fail());
}

/**
* Function to set velocity level
*/
void setVelocityLevel()
{
	bool isPositiveNum = true;

	//Require user enter 3 level of velocity
	//If user-entered is not digit then do this again
	do
	{
		try
		{
			isPositiveNum = true;

			//Enter 3 value of 3 velocity level
			cout << "CAI DAT VAN TOC CANH BAO KHOANG CACH AN TOAN VOI 3 MUC VAN TOC" << endl;
			for (int i = 0; i < 3; i++)
			{
				cout << "VAN TOC MUC " << i + 1 << ": ";
				cin >> car.str_arr_velocity[i];

				//If user does not enter a digit then throw warning
				if (!isDigit(car.str_arr_velocity[i]))
				{
					//throw warning message
					throw "VUI LONG CHI NHAP SO";
				}
				else if (!isPositiveNumber(car.arr_velocity[i]))      //If user does not enter a positive number then throw warning
				{
					//set isPositiveNum variable to false
					isPositiveNum = false;
					//throw warning message
					throw "VUI LONG KHONG NHAP SO AM";
				}

				//if user input valid value then cast str_arr_velocity[i] to int and assign it to arr_velocity[i]
				car.arr_velocity[i] = stoi(car.str_arr_velocity[i]);
			}
		}
		catch (const char* msg)     //catch warning message has been thrown
		{
			system("cls");
			//display caught warning message
			cerr << msg << endl;
		}
	} while (!isDigit(car.str_arr_velocity[0]) || !isDigit(car.str_arr_velocity[1]) || !isDigit(car.str_arr_velocity[2]) || !isPositiveNum);
}



/// A set of functions that display notification and menus

/**
* Function to display result password and default password before and after sort
*/
void displayResultPassword()
{

	system("cls");	//clear screen

	/* SELECTION SORT ALGORITHM */
	//Print out the array password user input before sort
	cout << "MANG NHAP VAO TRUOC KHI SAP XEP: ";
	printArray(car.arr_password, LENGTH);

	//The code calculates the time it takes to execute the selection sort algorithm
	//Get the timepoint before the function is called
	auto start_selectionSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	selectionSort(car.arr_password, LENGTH);
	//Get the timepoint after the function is called
	auto stop_selectionSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_selectionSort = duration_cast<microseconds>(stop_selectionSort_algorithm - start_selectionSort_algorithm);

	//Print out the array password user input after sort
	cout << "---> MANG NHAP VAO SAU KHI SAP XEP: ";
	printArray(car.arr_password, LENGTH);

	//Compare the complexity of selection sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_selectionSort.count() << " miliseconds" << endl;
	cout << endl;
	cout << endl;


	/* BUBBLE SORT ALGORITHM */
	//Print out the array default password before sort
	cout << "MA SO CA NHAN TRUOC KHI SAP XEP: ";
	printArray(car.arr_defaultPassword, LENGTH);

	//The code calculates the time it takes to execute the bubble sort algorithm
	//Get the timepoint before the function is called
	auto start_bubbleSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	bubbleSort(car.arr_defaultPassword);
	//Get the timepoint after the function is called
	auto stop_bubbleSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_bubbleSort = duration_cast<microseconds>(stop_bubbleSort_algorithm - start_bubbleSort_algorithm);

	//Print out the array default password after sort
	cout << "---> MA SO CA NHAN SAU KHI SAP XEP: ";
	printArray(car.arr_defaultPassword, LENGTH);

	//Compare the complexity of bubble sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_bubbleSort.count() << " miliseconds" << endl;
}

/**
* Function to display notification when speed is lower than velocity level 1
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void notificationLowerVelocityLv1(bool isOverSpeed)
{
	cout << " ----  TOC DO HIEN TAI LA: " << car.speed << " Km/h" << endl;
	cout << "BAN CHU Y GIU KHOANG CACH LA " << " 20 Km/h" << endl;
	if (isOverSpeed)
	{
		cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
	}
}

/**
* Function to display notification when speed is within velocity level 1 and level 2
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void notificationVelocityLv1ToLv2(bool isOverSpeed)
{
	cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/h" << endl;
	cout << "BAN CHU Y GIU KHOANG CACH LA " << " 55 Km/h" << endl;
	if (isOverSpeed)
	{
		cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
	}
}

/**
* Function to display notification when speed is within velocity level 2 and level 3
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void notificationVelocityLv2ToLv3(bool isOverSpeed)
{
	cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/h" << endl;
	cout << "BAN CHU Y GIU KHOANG CACH LA " << " 70 Km/h" << endl;
	if (isOverSpeed)
	{
		cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
	}
}

/**
* Function to display notification when speed is greater than velocity level 3
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void notificationHigherVelocityLv3(bool isOverSpeed)
{
	cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/h" << endl;
	cout << "BAN CHU Y GIU KHOANG CACH LA " << " 100 Km/h" << endl;
	if (isOverSpeed)
	{
		cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
	}
}

/**
* Function to display notification of Velocity Level
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void displayNotificationVelocityLevel(bool isOverSpeed)
{
	//Give notification when speed is lower than velocity level 1
	if (car.speed < car.arr_velocity[0])
	{
		notificationLowerVelocityLv1(isOverSpeed);
	}

	else if (car.speed >= car.arr_velocity[0] && car.speed < car.arr_velocity[1])     //Give notification when speed is within velocity level 1 and level 2
	{
		notificationVelocityLv1ToLv2(isOverSpeed);
	}

	else if (car.speed >= car.arr_velocity[1] && car.speed < car.arr_velocity[2])     //Give notification when speed is within velocity level 2 and level 3
	{
		notificationVelocityLv2ToLv3(isOverSpeed);
	}

	else        //Give notification when speed is higher than velocity level 3
	{
		notificationHigherVelocityLv3(isOverSpeed);
	}
}

/**
* Function display the notification about speed to screen
*/
void displayNotification()
{
	//display for R (Reverse) mode
	if (!car.isDrive)
	{
		//Case speed lower than 20 Km/h
		if (car.speed < 20)
		{
			displayNotificationVelocityLevel(false);
		}
		else    //Case speed greater than 20Km/h
		{
			displayNotificationVelocityLevel(true);
		}

	}

	else    //display for D (Drive) mode
	{
		//Case speed lower than 60 Km/h
		if (car.speed < 60)
		{
			displayNotificationVelocityLevel(false);
		}
		else    //Case speed greater than 60 Km/h
		{
			displayNotificationVelocityLevel(true);
		}
	}
}

/**
* Function display the Gearbox menu
*/
void gearBoxMenu()
{
	//Show menu and require user enter the choice
	//If user-entered is not digit then do this again
	do
	{
		//Show menu and require user enter the choice
		cout << "XIN MOI LUA CHON: " << endl;
		cout << "1. P" << endl;
		cout << "2. R" << endl;
		cout << "3. N" << endl;
		cout << "4. D" << endl;
		cout << "5. POWER OFF" << endl;
		cout << ">> ";
		cin >> car.str_gearChoice;
		//The case user input not a digit
		if (!isDigit(car.str_gearChoice))
		{
			system("cls");
			cout << "VUI LONG CHI NHAP SO \n" << endl;
		}
		else
		{
			car.gearChoice = stoi(car.str_gearChoice);
		}
	} while (!isDigit(car.str_gearChoice));
}

/**
* Function display Control Menu when user choice D or R on the Gearbox menu
*/
void controlMenu()
{
	//Show menu and require user enter the choice
	//If user-entered is not digit then do this again
	do
	{
		//Show menu and require user enter the choice
		cout << "MOI LUA CHON: " << endl;
		cout << "1. TANG TOC" << endl;
		cout << "2. GIAM TOC" << endl;
		cout << "3. PHANH" << endl;
		cout << "4. TRO VE MENU" << endl;
		cout << ">> ";
		cin >> car.str_controlChoice;
		//The case user input not a digit
		if (!isDigit(car.str_controlChoice))
		{
			system("cls");
			cout << "VUI LONG CHI NHAP SO\n" << endl;
			displayNotification();
		}
		else
		{
			system("cls");
			car.controlChoice = stoi(car.str_controlChoice);
			displayNotification();
		}
	} while (!isDigit(car.str_controlChoice));
}

/**
* Function set the speed of the car follow the user's choice on Control Menu (R mode or D mode)
*/
void setSpeed()
{
	//the cases user was chose in Control Menu
	switch (car.controlChoice)
	{
	case 1:   //case 1 speed up

			  //speed up to 5 Km/h
		car.speed += 5;
		//Clear screen
		system("cls");
		break;

	case 2:   //case 2: speed down

			  //speed down to 5 Km/h and check the speed after speed down
			  //If less than 0 Km/h, set speed to 0 Km/h
			  //If greater than 0, do nothing
		(car.speed -= 5) < 0 ? car.speed = 0 : car.speed = car.speed;

		//Clear screen
		system("cls");
		break;

	case 3:   //case 3: Brake
			  //set speed to 0 Km/h
		car.speed = 0;

		//Clear screen
		system("cls");
		break;

	case 4:     //case 4: Back to Gearbox menu
				//clear screen and do nothing
		system("cls");
		break;

	default:    //Throw warning when user does not choice from 1 to 4
				//Clear screen
		system("cls");

		cout << "VUI LONG CHON TU 1 DEN 4\n" << endl;
		break;
	}
}




