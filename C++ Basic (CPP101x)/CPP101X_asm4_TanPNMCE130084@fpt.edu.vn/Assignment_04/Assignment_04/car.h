#pragma once
#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <regex>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::chrono;

//Define length of array
#define LENGTH 8
#define FILE_PATH "AMS03.dat"

class Car {
private:
	int arr_password[LENGTH];			//The variable saves the user-entered password
	int arr_velocity[3];				//The variable saves value cast str_arr_velocity variable from string to int

public:
	Car();
	Car(int password[LENGTH], int distance[3]);
	int* getPassword();
	int getPasswordAtIndex(int);
	void setPassword(int arr[]);
	void setPassword();
	void setPasswordAtIndex(int, int);

	int* getDistance();
	int getDistanceAtIndex(int);
	void setDistance(int arr[]);
	void setDistance();
	void setDistanceAtIndex(int, int);
	void writeToFile(Car car, ofstream &file_out);
	void readFromFile(Car car, ifstream &file_in);
};

#endif // CAR_H_INCLUDED
