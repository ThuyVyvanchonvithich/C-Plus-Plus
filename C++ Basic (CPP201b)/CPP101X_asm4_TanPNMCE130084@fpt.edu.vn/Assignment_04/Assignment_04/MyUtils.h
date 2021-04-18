#pragma once
#ifndef MYUTILS_H_INCLUDED
#define MYUTILS_H_INCLUDED

#include "car.h"

/**
* define the global variables for car used in file
*/
typedef struct CarDrive
{
	int arr_defaultPassword[LENGTH];	//The variable saves the user-entered password
	string str_gearChoice;				//The variable saves the user's choice on menu Gearbox
	int gearChoice;						//The variable saves value cast str_gearChoice variable from string to int
	string str_controlChoice;			//The variable saves the user's choice R or D on menu Gearbox
	int controlChoice;					//The variable saves value cast str_controlChoice variable from string to int
	int speed;							//The variable saves current speed
	string str_arr_velocity[3];			//The variable save speed of velocity levels that user-entered
	bool isDrive;						//The variable saves the state of the Gearbox is D (Drive) mode or not
	//string repeatChoice;				//The variable saves the user's choice Yes or No to re-setup data in file
};

/**
* define the global variables for compare algorithm used in file
*/
typedef struct CompareAlgorithm
{
	int count_timesTraversal;		//The variable saves the number of times the algorithm traverses the elements in the array
};


/** Forward declaration for functions used in file */

bool isFileExist(ifstream &file_in);

///A set of algorithm processing functions
void swap(int*, int*);
void bubbleSort(int *arr, int size);
int* selectionSort(int *arr, int size);
void printArray(int arr[3], int size);
void printVelocityLevel(int velocity_level[]);

///A set of check functions
bool isMatch(int arr1[], int arr2[]);
bool isDigit(std::string);
bool isPositiveNumber(int);

///A set of input functions
int inputPassword(int arr_password[]);
Car setVelocityLevel(Car);

///A set of function file handle
//int readFromFile(int arr[], ifstream &file_in);
//void writeToFile(int arr[], int size, ofstream &file_out);
Car loginHandler(Car, bool);
Car distanceHandler(Car, bool);

///A set of functions that display notification and menus
Car displayResultPassword(Car &car, int arrPWD[]);
void notificationLowerVelocityLv1(bool);
void notificationVelocityLv1ToLv2(bool);
void notificationVelocityLv2ToLv3(bool);
void notificationHigherVelocityLv3(bool);
void displayNotificationVelocityLevel(Car, bool);
void displayNotification(Car);
void gearBoxMenu();
void controlMenu(Car);

void setSpeed();
void compareSortAlgorithm();
void menuHandler(Car);
void powerOff();

#endif // CAR_H_INCLUDED