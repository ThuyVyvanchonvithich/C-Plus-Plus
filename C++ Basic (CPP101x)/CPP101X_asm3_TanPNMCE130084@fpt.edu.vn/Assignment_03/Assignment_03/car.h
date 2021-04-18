#pragma once
#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
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
	int arr_defaultPassword[LENGTH];	//The variable saves the user-entered password
	int arr_password[LENGTH];			//The variable saves the user-entered password
	std::string str_gearChoice;         //The variable saves the user's choice on menu Gearbox
	int gearChoice;						//The variable saves value cast str_gearChoice variable from string to int
	std::string str_controlChoice;		//The variable saves the user's choice R or D on menu Gearbox
	int controlChoice;					//The variable saves value cast str_controlChoice variable from string to int
	int speed;							//The variable saves current speed
	std::string str_arr_velocity[3];    //The variable save speed of velocity levels that user-entered
	int arr_velocity[3];				//The variable saves value cast str_arr_velocity variable from string to int
	bool isDrive;						//The variable saves the state of the Gearbox is D (Drive) mode or not
	string repeatChoice;				//The variable saves the user's choice Yes or No to re-setup data in file
};
//CarDrive car;   //define alter name for CarDrive

/**
* define the global variables for compare algorithm used in file
*/
typedef struct CompareAlgorithm
{
	int count_timesTraversal;		//The variable saves the number of times the algorithm traverses the elements in the array
};
//CompareAlgorithm cmp;   //define alter name for CompareAlgorithm

/** Forward declaration for functions used in file */

///A set of algorithm processing functions
void swap(int, int);
void bubbleSort(int arr[]);
void selectionSort(int arr[], int size);
void printArray(int arr[3], int size);
void printVelocityLevel(int velocity_level[]);

///A set of check functions
bool isMatch(int arr1[], int arr2[]);
bool isDigit(std::string);
bool isPositiveNumber(int);

///A set of input functions
int inputPassword(int arr_password[]);
void setVelocityLevel(int arr_velocity[]);

///A set of function file handle
int readFromFile(int arr[], ifstream &file_in);
void writeToFile(int arr[], int size, ofstream &file_out);
void loginHandler();
int distanceHandler();

///A set of functions that display notification and menus
void resultLogin(int defaultPassword[], int arrPWD[]);
void notificationLowerVelocityLv1(bool);
void notificationVelocityLv1ToLv2(bool);
void notificationVelocityLv2ToLv3(bool);
void notificationHigherVelocityLv3(bool);
void displayNotificationVelocityLevel(bool);
void displayNotification();
void gearBoxMenu();
void controlMenu();

void setSpeed();
void menuHandler();
void powerOff();

#endif // CAR_H_INCLUDED
