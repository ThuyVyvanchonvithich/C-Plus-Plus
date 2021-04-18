#include "car.h"
#include "MyUtils.h"



#pragma region Define code to getter and setter of object class Car

/* Create constructor no params and have 2 params*/
Car::Car() {
}

Car::Car(int password[LENGTH], int distance[3]) {
	setPassword(password);
	setDistance(distance);
}


/**
* Get array password
*/
int* Car::getPassword() {
	return this->arr_password;
}

/**
* Get value of password at index i
*/
int Car::getPasswordAtIndex(int i) {
	return this->arr_password[i];
}

/**
* Set an array to array password of object
*/
void Car::setPassword(int arr[LENGTH]) {
	std::copy(arr, arr + LENGTH, this->arr_password);
}

/**
* Require user input password and set it to array password
*/
void Car::setPassword() {
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
				cin >> this->arr_password[i];

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
* Set value to password at index i
*/
void Car::setPasswordAtIndex(int value, int i) {
	this->arr_password[i] = value;
}

/**
* Get an array safe distance
*/
int* Car::getDistance() {
	return this->arr_velocity;
}

/**
* get value of safe distance at index i
*/
int Car::getDistanceAtIndex(int i) {
	return this->arr_velocity[i];
}

/**
* Set an array safe distance
*/
void Car::setDistance(int arr[3]) {
	std::copy(arr, arr + 3, this->arr_velocity);
}

/**
* Set value to array safe distance at index i
*/
void Car::setDistanceAtIndex(int velocity, int i) {
	this->arr_velocity[i] = velocity;
}

#pragma endregion

///A set of function file handle
/**
* Function to read data from file
*/
void Car::readFromFile(Car car, ifstream &file_in) {

	file_in.read((char *)&car, sizeof(Car));
}

/**
* Function to write data to file
*/
void Car::writeToFile(Car car, ofstream &file_out) {

	file_out.write((char *)&car, sizeof(Car));
}
