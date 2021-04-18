#include "car.h"
#include "MyUtils.h"

//define alter name for CarDrive
CarDrive carDrive;
//define alter name for CompareAlgorithm
CompareAlgorithm cmp;

/** All Function used in this file */

bool isFileExist(ifstream &file_in) {
	if (file_in.fail()) {
		return false;
	}
	else {
		return true;
	}
}

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
void bubbleSort(int *arr, int size)
{
	cmp.count_timesTraversal = 0;
	for (int i = 0; i < size; i++) {
		cmp.count_timesTraversal++;
		for (int j = i + 1; j < size; j++)
		{
			cmp.count_timesTraversal++;
			if (*(arr + i) > *(arr + j))
			{
				swap((arr + j), (arr + i));
			}
		}
	}
}

/**
* Function to implement selection sort algorithm
*
* @param arr[] - the array want to sort
*/
int* selectionSort(int *arr, int size)
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
			if (*(arr + j) < *(arr + min_index))
			{
				min_index = j;
			}
		}

		// Swap the found minimum element with the first element
		//swap(*(&arr[min_index]), *(&arr[i]));
		swap((arr + min_index), (arr + i));
	}
	return arr;
}

/**
* Function to print an array
*
* @param arr[] - the array want to display
*/
void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printVelocityLevel(int velocity_level[]) {

	for (int i = 0; i < 3; i++)
	{
		cout << "VAN TOC MUC " << i + 1 << ": " << velocity_level[i] << endl;
	}
}



/// A set of check functions

/**
* Function to check whether 2 arrays are the same or not
*
* @param arr1[] - the first array wants to compare
* @param arr2[] - the second array wants to compare
*/
bool isMatch(int arr1[], int arr2[])
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
int inputPassword(int arr_password[])
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
				//cin >> *car.arr_password[i];
				cin >> arr_password[i];

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

	return *arr_password;
}

/**
* Function to set velocity level
*/
Car setVelocityLevel(Car car)
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
				cin >> carDrive.str_arr_velocity[i];

				//If user does not enter a digit then throw warning
				if (!isDigit(carDrive.str_arr_velocity[i]))
				{
					//throw warning message
					throw "VUI LONG CHI NHAP SO";
				}


				//if user input valid value then cast str_arr_velocity[i] to int and assign it to arr_velocity[i]
				//arr_velocity[i] = stoi(carDrive.str_arr_velocity[i]);
				car.setDistanceAtIndex(stoi(carDrive.str_arr_velocity[i]), i);
				//cout << "distance " << i << "= " << car.getDistanceAtIndex(i) << endl;

				if (!isPositiveNumber(car.getDistanceAtIndex(i)))      //If user does not enter a positive number then throw warning
				{
					//set isPositiveNum variable to false
					isPositiveNum = false;
					//throw warning message
					throw "VUI LONG KHONG NHAP SO AM";
				}
			}
		}
		catch (const char* msg)     //catch warning message has been thrown
		{
			system("cls");
			//display caught warning message
			cerr << msg << endl;
		}
	} while (!isDigit(carDrive.str_arr_velocity[0]) || !isDigit(carDrive.str_arr_velocity[1]) || !isDigit(carDrive.str_arr_velocity[2]) || !isPositiveNum);

	int *arr_temp = new int[3];
	std::copy(car.getDistance(), car.getDistance() + 3, arr_temp);
	arr_temp = selectionSort(arr_temp, 3);
	car.setDistance(arr_temp);

	return car;
}





/**
* Function to handle about user input password and validation this password.
* After that, allows users to reset passwords
*
* @param Car - object car
* @param isFileExist - file is exist or not
*/
Car loginHandler(Car car, bool isFileExist) {

	int arr_password[8];

	if (isFileExist == false) {
		cout << "DAY LA LAN DAU TIEN BAN SU DUNG CHUONG TRINH" << endl;
		cout << "VUI LONG TAO MA SO CA NHAN" << endl;

		//require user set up the key personal in the first time use program
		car.setPassword();
	}
	else {

		//Require user input the password
		*arr_password = inputPassword(arr_password);

		//Sort -> compare password user-entered and allow users reset their password 
		car = displayResultPassword(car, arr_password);
	}

	return car;
}

/**
* Function to handle set distance based on the choice of user.
* After that, return turn array safe distance
*
* @param Car - object car
* @param isFileExist - file is exist or not
*/
Car distanceHandler(Car car, bool isFileExist) {

	//declare variable
	int arr_velocity[3];
	string repeatChoice;	//The variable saves the user's choice Yes or No to re-setup data in file


	//check file is exist or not
	//if file is not exist then notify to user and create new file
	if (isFileExist == false) {

		//show notification
		cout << "VUI LONG TAO KHOANG CACH AN TOAN" << endl;

		//set safe distance
		car = setVelocityLevel(car);
	}
	else {
		std::copy(car.getDistance(), car.getDistance() + 3, arr_velocity);

		//Show 3 level safe distance which user seted off
		cout << "3 MUC VAN TOC BAN DA CAI DAT:" << endl;
		printVelocityLevel(arr_velocity);

		//Over and over again constantly if user don't enter Yes(Y or y) or No(N or n)
		do {
			//Ask if the user wants to change password they seted off or not 
			cout << "BAN CO MUON THAY DOI MUC VAN TOC HAY KHONG? Y/N?" << endl;
			cout << "> ";
			cin >> repeatChoice;

			//case user enter Yes (Y or y)
			if (repeatChoice == "Y" || repeatChoice == "y") {
				system("cls");
				//set safe distance
				car = setVelocityLevel(car);

				//Show safe distance user-entered again
				system("cls");

				//print out the safe distance after seted off
				cout << "3 MUC VAN TOC BAN VUA CAI DAT LAI:" << endl;
				printVelocityLevel(car.getDistance());

				system("pause");
				break;
			}
			else if (repeatChoice == "n" || repeatChoice == "N") {	//case user enter No (N or n)
				break;
			}
			else {	//case user don't enter Yes or No
				system("cls");
				cout << "VUI LONG CHON Y/N" << endl;
			}
		} while (repeatChoice != "N" || repeatChoice != "n"
			|| repeatChoice != "Y" || repeatChoice != "y");
	}

	return car;
}



/// A set of functions that display notification and menus
/**
* Function to display result password and default password before and after sort.
* After that, show result login
*/
Car displayResultPassword(Car &car, int arrPWD[])
{
	int *defaultPassword = new int[LENGTH];
	//copy password get from file to variable default password to compare with password user-entered
	std::copy(car.getPassword(), car.getPassword() + LENGTH, defaultPassword);
	system("cls");	//clear screen

#pragma region Sort user-entered password

	/* SELECTION SORT ALGORITHM */
	//Print out the array password user input before sort
	cout << "MANG NHAP VAO TRUOC KHI SAP XEP: ";
	printArray(arrPWD, LENGTH);

	//The code calculates the time it takes to execute the selection sort algorithm
	//Get the timepoint before the function is called
	auto start_selectionSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	selectionSort(arrPWD, LENGTH);
	//Get the timepoint after the function is called
	auto stop_selectionSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_selectionSort = duration_cast<microseconds>(stop_selectionSort_algorithm - start_selectionSort_algorithm);

	//Print out the array password user input after sort
	cout << "---> MANG NHAP VAO SAU KHI SAP XEP: ";
	printArray(arrPWD, LENGTH);

	//Compare the complexity of selection sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_selectionSort.count() << " miliseconds" << endl;
	cout << endl;
	cout << endl;
#pragma endregion


#pragma region Sort user-entered password

	/* BUBBLE SORT ALGORITHM */
	//Print out the array default password before sort
	cout << "MA SO CA NHAN TRUOC KHI SAP XEP: ";
	printArray(defaultPassword, LENGTH);

	//The code calculates the time it takes to execute the bubble sort algorithm
	//Get the timepoint before the function is called
	auto start_bubbleSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	bubbleSort(defaultPassword, LENGTH);
	//Get the timepoint after the function is called
	auto stop_bubbleSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_bubbleSort = duration_cast<microseconds>(stop_bubbleSort_algorithm - start_bubbleSort_algorithm);

	//Print out the array default password after sort
	cout << "---> MA SO CA NHAN SAU KHI SAP XEP: ";
	printArray(defaultPassword, LENGTH);

	//Compare the complexity of bubble sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_bubbleSort.count() << " miliseconds" << endl;
#pragma endregion


#pragma region Login result

	string repeatChoice;	//The variable saves the user's choice Yes or No to re-setup data in file

	//Check whether password and default password after sort are the same or not
	//If not same then give goodbye message and stop program
	if (!isMatch(arrPWD, defaultPassword))
	{

		cout << endl;
		cout << "MA SO CA NHAN KHONG HOP LE!!!" << endl;
		cout << "UNG DUNG DA BI DONG!!!" << endl;

		exit(0);
	}
	else    //if same then pause screen
	{

		//Over and over again constantly if user don't enter Yes(Y or y) or No(N or n)
		do {
			//Ask if the user wants to change password they seted off or not 
			cout << "BAN CO MUON THAY DOI MA SO CA NHAN HAY KHONG? Y (YES)/ N (NO) ?" << endl;
			cout << "> ";
			cin >> repeatChoice;

			//case user enter Yes (Y or y)
			if (repeatChoice == "Y" || repeatChoice == "y") {
				system("cls");
				cout << "MOI THIET LAP MA SO CA NHAN MOI" << endl;

				//Require user input the new key personal
				car.setPassword();

				cout << endl;
				cout << "THIET LAP MA SO CA NHAN MOI THANH CONG!!!" << endl;
				cout << endl;
				system("pause");
				break;
			}
			else if (repeatChoice == "n" || repeatChoice == "N") {	//case user enter No (N or n)
				break;
			}
			else {	//case user don't enter Yes or No
				system("cls");
				cout << "VUI LONG CHON Y/N" << endl;
			}
		} while (repeatChoice != "N" || repeatChoice != "n"
			|| repeatChoice != "Y" || repeatChoice != "y");
	}
#pragma endregion

	return car;
}

/**
* Function to display notification when speed is lower than velocity level 1
*
* @param isOverSpeed - the boolean variable indicates over speed or not
*/
void notificationLowerVelocityLv1(bool isOverSpeed)
{
	cout << " ----  TOC DO HIEN TAI LA: " << carDrive.speed << " Km/h" << endl;
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
	cout << "----  TOC DO HIEN TAI LA: " << carDrive.speed << " Km/h" << endl;
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
	cout << "----  TOC DO HIEN TAI LA: " << carDrive.speed << " Km/h" << endl;
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
	cout << "----  TOC DO HIEN TAI LA: " << carDrive.speed << " Km/h" << endl;
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
void displayNotificationVelocityLevel(Car car, bool isOverSpeed)
{
	//Give notification when speed is lower than velocity level 1
	if (carDrive.speed < car.getDistanceAtIndex(0))
	{
		notificationLowerVelocityLv1(isOverSpeed);
	}

	else if (carDrive.speed >= car.getDistanceAtIndex(0) && carDrive.speed < car.getDistanceAtIndex(1))     //Give notification when speed is within velocity level 1 and level 2
	{
		notificationVelocityLv1ToLv2(isOverSpeed);
	}

	else if (carDrive.speed >= car.getDistanceAtIndex(1) && carDrive.speed < car.getDistanceAtIndex(2))     //Give notification when speed is within velocity level 2 and level 3
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
void displayNotification(Car car)
{
	//display for R (Reverse) mode
	if (!carDrive.isDrive)
	{
		//Case speed lower than 20 Km/h
		if (carDrive.speed < 20)
		{
			displayNotificationVelocityLevel(car, false);
		}
		else    //Case speed greater than 20Km/h
		{
			displayNotificationVelocityLevel(car, true);
		}

	}

	else    //display for D (Drive) mode
	{
		//Case speed lower than 60 Km/h
		if (carDrive.speed < 60)
		{
			displayNotificationVelocityLevel(car, false);
		}
		else    //Case speed greater than 60 Km/h
		{
			displayNotificationVelocityLevel(car, true);
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
		cout << "5. Compare algorithm" << endl;
		cout << "6. POWER OFF" << endl;
		cout << ">> ";
		cin >> carDrive.str_gearChoice;
		//The case user input not a digit
		if (!isDigit(carDrive.str_gearChoice))
		{
			system("cls");
			cout << "VUI LONG CHI NHAP SO \n" << endl;
		}
		else
		{
			carDrive.gearChoice = stoi(carDrive.str_gearChoice);
		}
	} while (!isDigit(carDrive.str_gearChoice));
}

/**
* Function display Control Menu when user choice D or R on the Gearbox menu
*/
void controlMenu(Car car)
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
		cin >> carDrive.str_controlChoice;
		//The case user input not a digit
		if (!isDigit(carDrive.str_controlChoice))
		{
			system("cls");
			cout << "VUI LONG CHI NHAP SO\n" << endl;
			displayNotification(car);
		}
		else
		{
			system("cls");
			carDrive.controlChoice = stoi(carDrive.str_controlChoice);
			displayNotification(car);
		}
	} while (!isDigit(carDrive.str_controlChoice));
}

/**
* Function set the speed of the car follow the user's choice on Control Menu (R mode or D mode)
*/
void setSpeed()
{
	//the cases user was chose in Control Menu
	switch (carDrive.controlChoice)
	{
	case 1:   //case 1 speed up

		//speed up to 5 Km/h
		carDrive.speed += 5;
		//Clear screen
		system("cls");
		break;

	case 2:   //case 2: speed down

		//speed down to 5 Km/h and check the speed after speed down
		//If less than 0 Km/h, set speed to 0 Km/h
		//If greater than 0, do nothing
		(carDrive.speed -= 5) < 0 ? carDrive.speed = 0 : carDrive.speed = carDrive.speed;

		//Clear screen
		system("cls");
		break;

	case 3:   //case 3: Brake
		//set speed to 0 Km/h
		carDrive.speed = 0;

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

void compareSortAlgorithm() {
	//declare array
	int *arr1 = new int[32]{ 11, 37, 20, 46, 6, 37, 19, 16, 26, 47, 27, 10, 44, 5, 4, 12, 15, 20, 36, 29,
	31, 2, 11, 50, 63, 14, 5, 0, 34, 55, 23, 45 };
	int *arr2 = new int[32]{ 11, 37, 20, 46, 6, 37, 19, 16, 26, 47, 27, 10, 44, 5, 4, 12, 15, 20, 36, 29,
	31, 2, 11, 50, 63, 14, 5, 0, 34, 55, 23, 45 };

#pragma region Sort user-entered password

	/* SELECTION SORT ALGORITHM */
	//Print out the array password user input before sort
	cout << "MANG NHAP VAO TRUOC KHI SAP XEP: ";
	printArray(arr1, 32);

	//The code calculates the time it takes to execute the selection sort algorithm
	//Get the timepoint before the function is called
	auto start_selectionSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	selectionSort(arr1, 32);
	//Get the timepoint after the function is called
	auto stop_selectionSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_selectionSort = duration_cast<microseconds>(stop_selectionSort_algorithm - start_selectionSort_algorithm);

	//Print out the array password user input after sort
	cout << "---> MANG NHAP VAO SAU KHI SAP XEP: ";
	printArray(arr1, 32);

	//Compare the complexity of selection sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_selectionSort.count() << " miliseconds" << endl;
	cout << endl;
	cout << endl;
#pragma endregion


#pragma region Sort user-entered password

	/* BUBBLE SORT ALGORITHM */
	//Print out the array default password before sort
	cout << "MA SO CA NHAN TRUOC KHI SAP XEP: ";
	printArray(arr2, 32);

	//The code calculates the time it takes to execute the bubble sort algorithm
	//Get the timepoint before the function is called
	auto start_bubbleSort_algorithm = high_resolution_clock::now();
	//Sort the user-entered password
	bubbleSort(arr2, 32);
	//Get the timepoint after the function is called
	auto stop_bubbleSort_algorithm = high_resolution_clock::now();
	//Calculates the time to execute the algorithm
	auto execute_time_bubbleSort = duration_cast<microseconds>(stop_bubbleSort_algorithm - start_bubbleSort_algorithm);

	//Print out the array default password after sort
	cout << "---> MA SO CA NHAN SAU KHI SAP XEP: ";
	printArray(arr2, 32);

	//Compare the complexity of bubble sort algorithm
	cout << "** DO PHUC TAP KHI SU DUNG GIAI THUAT SELECTION SORT **" << endl;
	cout << "---> SO LAN DUYET QUA CAC PHAN TU TRONG MANG: " << cmp.count_timesTraversal << " times" << endl;
	cout << "---> THOI GIAN THUC THI GIAI THUAT: " << execute_time_bubbleSort.count() << " miliseconds" << endl;
	cout << endl;
#pragma endregion

	system("pause");
}

/**
* Method to handle menu gearbox
*/
void menuHandler(Car car)
{
	//Show Gearbox menu
	//Over and over again constantly until user choice POWER OFF
	do
	{
		//system("cls");
		gearBoxMenu();

		//The cases user was chose
		switch (carDrive.gearChoice)
		{
		case 1:     //case 1: P (Park)
			//Clear screen
			system("cls");

			if (carDrive.speed > 0)
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
				if (carDrive.isDrive && carDrive.speed > 0)
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
					if (carDrive.speed == 0 && carDrive.controlChoice != 2 && carDrive.controlChoice != 3)
					{
						carDrive.speed = 7;
						//set state D mode to false
						carDrive.isDrive = false;
						displayNotification(car);
					}
					else        //car has not been stopped
					{
						//set state D mode to false
						carDrive.isDrive = false;
						//show information about current speed
						displayNotification(car);
					}

					//show Menu D or R mode
					controlMenu(car);
					//set speed for car
					setSpeed();
				}
			} while (carDrive.controlChoice != 4);
			break;

		case 3:   //case 3: N (Neutral)
			//Clear screen
			system("cls");

			//Check speed is 0 Km/h or not
			//if is not 0 Km/h then show warning
			if (carDrive.speed > 0)
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
				if (!carDrive.isDrive && carDrive.speed > 0)
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
					if (carDrive.speed == 0 && carDrive.controlChoice != 3 && carDrive.controlChoice != 2)
					{
						carDrive.speed = 7;
						carDrive.isDrive = true;
						displayNotification(car);
					}
					else        //car has not been stopped
					{
						//set state D mode to false
						carDrive.isDrive = true;
						//show information about current speed
						displayNotification(car);
					}

					//show Menu D or R mode
					controlMenu(car);
					//set speed for car
					setSpeed();
				}
			} while (carDrive.controlChoice != 4);
			break;

		case 5:     //case 5: Compare 2 sort algorithm
			//Clear screen
			system("cls");

			//call function to compare 2 sort algorithm
			compareSortAlgorithm();
			system("cls");
			break;

		case 6:		//case 6: POWER OFF
			//Clear screen
			system("cls");
			break;

		default:    //Throw warning when user does not choice from 1 to 5
			//Clear screen
			system("cls");
			//show warning message
			cout << "VUI LONG CHON TU 1 DEN 6\n" << endl;
			break;
		}
	} while (carDrive.gearChoice != 6);
}

/**
* Function power off
*/
void powerOff()
{

	//show goodbye notice
	cout << "*---------------- POWER OFF ---------------*" << endl;
	cout << "*                                          *" << endl;
	cout << "*      CAM ON VI DA SU DUNG PHAN MEM       *" << endl;
	cout << "*                                          *" << endl;
	cout << "********************************************" << endl;
}