#include <iostream>
#include "General.h"
#include "Display.h"
#include "Sound.h"
#include "CommonInfo.h"	
#include "BinaryTree.h"
#include <fstream>
#include <regex>
#include <set>

// 3 Struct to sort Set
struct cmpDisplay {
	bool operator() (Display* a, Display* b) { return (*a).getCarName() < (*b).getCarName(); }
};

struct cmpSound {
	bool operator() (Sound* a, Sound* b) { return (*a).getCarName() < (*b).getCarName(); }
};

struct cmpGeneral {
	bool operator() (General* a, General* b) { return (*a).getCarName() < (*b).getCarName(); }
};

// Declare binary tree
BinaryTree* treeDisplay = new BinaryTree;
BinaryTree* treeSound = new BinaryTree;
BinaryTree* treeGeneral = new BinaryTree;

//declare object
Display *display = new Display();
Sound *sound = new Sound();
General *general = new General();
Setting *setting = new Setting();

//declare global variables
int displayType = 1, soundType = 2, generalType = 3, settingType = 4;	//Type to show data
int displayCount, soundCount, generalCount = 0;
int settingCount = 0;
int position = 0;	// The variables to store index of exist element 

//declare vector to store Timezone and Language
vector<CommonInfo> timezoneList;
vector<CommonInfo> languageList;

/// Forward declaration
void NhapThongTinCaiDat();
void XuatThongTinCaiDat();
void XuatThongTinCaiDat(int sortType);
int selectType();

void XuatThongTinCaiDat_Sound(int sortType);
void XuatThongTinCaiDat_General(int sortType);
void XuatThongTinCaiDat_Display(int sortType);
void printSearchResult(Node * resultDisplay, Node * resultSound, Node * resultGeneral);
void XuatThongTatCaTinCaiDat();

void NhapThongTinCaiDat_Sound();
void NhapThongTinCaiDat_General();
void NhapThongTinCaiDat_Display();

void downloadTimeZone();
void downloadLanguage();

void writeDataToFile();
void readDataFromFile();
void handleDataInFile(string data);
bool isKeyExisted(Node* node);

string getStringTimezone(string timezone);

// Sort data
bool comparatorTimezone(CommonInfo c1, CommonInfo c2);
bool comparatorLanguage(CommonInfo c1, CommonInfo c2);

void menu();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {

	downloadLanguage();
	downloadTimeZone();
	readDataFromFile();
	menu();

	return 0;
}

/*
* The function to run menu
*/
void menu() {
	int selection;
	bool error = false;
	regex isNumber("^[0-3]");
	string user_choice;

	do {
		error = false;
		system("cls");
		cout << "----- SELECT MENU -----" << endl;
		cout << "1. Input setting information" << endl;
		cout << "2. Print setting information" << endl;
		cout << "3. Exit" << endl;
		cout << "Your selection: ";
		cin >> user_choice;
		if (!regex_match(user_choice, isNumber))
		{
			cout << "Please enter a number from 1 to 3!" << endl;
			system("pause");
			cin.ignore(256, '\n');
			error = true;
		}
	} while (error == true);

	selection = stoi(user_choice);
	system("cls");
	switch (selection)
	{
	case 1:
		NhapThongTinCaiDat();
		break;

	case 2:
		XuatThongTinCaiDat();
		break;

	case 3:
		writeDataToFile();

		// Free memory
		delete treeDisplay;
		delete treeSound;
		delete treeGeneral;
		cout << "THANKS FOR USE MY PROGRAM!!!" << endl;
		exit(0);

	}
}

/*
* The function to handle menu input setting information
*/
void NhapThongTinCaiDat() {
	//declare local variables and string regex
	int selection;
	bool error = false;
	regex isDigit("^[0-3]");
	string user_choice;

	//Over and over again constantly until user choice Exit
	do {

		do {
			error = false;
			system("cls");

			//display menu
			cout << " --- SELECT MENU --- " << endl;
			cout << " 1. Display setting" << endl;
			cout << " 2. Sound setting" << endl;
			cout << " 3. General setting" << endl;
			cout << " 0. Exit" << endl;
			cout << " Your selection: ";
			cin >> user_choice;

			//catch the case user input is not a number and from 0 to 3
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Please enter a number from 0 to 3!" << endl;
				system("pause");
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);

		selection = stoi(user_choice);	//cast string to int
		system("cls");

		//Handle the cases user choose
		switch (selection) {

		case 1:		//case 1 input thong tin Display
			cout << " --- Ban nhap thong tin Display --- " << endl;
			NhapThongTinCaiDat_Display();
			break;

		case 2:		//case 2 input thong tin Sound
			cout << " --- Ban nhap thong tin Sound --- " << endl;
			NhapThongTinCaiDat_Sound();
			break;

		case 3:		//case 3 input thong tin General
			cout << " --- Ban nhap thong tin General --- " << endl;
			NhapThongTinCaiDat_General();
			system("cls");
			break;

		case 0:		//case 0 Exit
			menu();
			break;
		}
	} while (selection != 0);
}

/*
* The function to input data of Sound
*/
void NhapThongTinCaiDat_Sound()
{
	string continues = "n";
	bool existed = false;	// The variables to check owner name is exist or not

	//Over and over again constantly until user choice No (do not want to add new Sound)
	do {

		// Declare Setting and node Sound
		Setting st;
		Node* nodeSound;
		
		// Require user input data of setting and check the Owner name is exist or not
		// If the owner name is exist then require user input setting again
		do {

			existed = false;	//Reset value of variable existed

			system("cls");
			cout << "--- Input Sound setting ---" << endl;
			cout << "Index car: " << soundCount + 1 << "\n";
			
			//Require user input setting data
			st = setting->nhapThongTin();

			// Find the Owner name user-entered in tree Sound
			Node* nodeSoundName = treeSound->searchByName(st.getCarName());
			// Find the Personal key user-entered in tree Sound
			nodeSound = treeSound->searchByPersonalKey(st.getPersonalKey());

			// If the Owner name is exist but Personal key is not exist, then send warning message
			if (isKeyExisted(nodeSoundName) && !isKeyExisted(nodeSound)) {

				// Display warning message
				cout << endl;
				cout << "-- WARNING: The Owner name have been existed, please enter another name!!! --" << endl;
				cout << endl;

				system("pause");
				existed = true;
			}

		} while (existed == true);

		//Initialize Sound
		Sound* s = new Sound(st);

		// Find the node is store personal key that user input
		Node* nodeDisplay = treeDisplay->searchByPersonalKey(st.getPersonalKey());
		Node* nodeGeneral = treeGeneral->searchByPersonalKey(st.getPersonalKey());

		// The case user input personal key is exist
		if (isKeyExisted(nodeSound))
		{
			//Update setting
			nodeSound->data->updateSetting(st);
			nodeDisplay->data->updateSetting(st);
			nodeGeneral->data->updateSetting(st);

			//Message
			cout << "-> This car already existed, data will be overriten" << endl;

			s->nhapThongTin(st);
			dynamic_cast<Sound*>(nodeSound->data)->updateSound(st, s->get_media_level(), s->get_call_level(), s->get_navi_level(), s->get_notification_level());

		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			// Add new Sound
			s->nhapThongTin(st);	//require user input data of Sound
			treeSound->insert(s);

			//Add empty Display and General
			treeDisplay->insert(new Display(st));
			treeGeneral->insert(new General(st));
			soundCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << soundCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to input data of General
*/
void NhapThongTinCaiDat_General()
{
	string continues = "n";
	bool existed = false;	// The variables to check owner name is exist or not

	//Over and over again constantly until user choice No (do not want to add new General)
	do {

		// Declare Setting and node General
		Setting st;
		Node* nodeGeneral;

		// Require user input data of setting and check the Owner name is exist or not
		// If the owner name is exist then require user input setting again
		do {

			existed = false;	//Reset value of variable existed

			system("cls");
			cout << "--- Input General setting ---" << endl;
			cout << "Index car: " << generalCount + 1 << "\n";
			
			//Require user input setting data
			st = setting->nhapThongTin();

			// Find the Owner name user-entered in tree General
			Node* nodeGeneralName = treeGeneral->searchByName(st.getCarName());
			// Find the Personal key user-entered in tree Sound
			nodeGeneral = treeGeneral->searchByPersonalKey(st.getPersonalKey());

			// If the Owner name is exist but Personal key is not exist, then send warning message
			if (isKeyExisted(nodeGeneralName) && !isKeyExisted(nodeGeneral)) {

				// Display warning message
				cout << endl;
				cout << "-- WARNING: The Owner name have been existed, please enter another name!!! --" << endl;
				cout << endl;

				system("pause");
				existed = true;
			}

		} while (existed == true);

		//Initalize General
		General* g = new General(st);

		// Find the node is store personal key that user input
		Node* nodeSound = treeSound->searchByPersonalKey(st.getPersonalKey());
		Node* nodeDisplay = treeDisplay->searchByPersonalKey(st.getPersonalKey());

		// The case user input personal key is exist
		if (isKeyExisted(nodeGeneral))
		{
			//Update setting
			nodeSound->data->updateSetting(st);
			nodeDisplay->data->updateSetting(st);
			nodeGeneral->data->updateSetting(st);

			//Message
			cout << "-> This car already existed, data will be overriten" << endl;

			g->nhapThongTin(st);
			dynamic_cast<General*>(nodeGeneral->data)->updateGeneral(st, g->get_timeZone(), g->get_language());
		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			//Add new Sound
			g->nhapThongTin(st);	//require user input data of General
			treeGeneral->insert(g);

			//Add empty Display and Sound
			treeDisplay->insert(new Display(st));
			treeSound->insert(new Sound(st));
			generalCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << generalCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to input data of Display
*/
void NhapThongTinCaiDat_Display()
{
	string continues = "n";
	bool existed = false;	// The variables to check owner name is exist or not

	//Over and over again constantly until user choice No (do not want to add new Display)
	do {

		// Declare Setting and node Display
		Setting st;
		Node* nodeDisplay;

		// Require user input data of setting and check the Owner name is exist or not
		// If the owner name is exist then require user input setting again
		do {

			existed = false;	//Reset value of variable existed

			system("cls");
			cout << "--- Input Sound setting ---" << endl;
			cout << "Index car: " << displayCount + 1 << "\n";
			
			//Require user input setting data
			st = setting->nhapThongTin();

			// Find the Owner name user-entered in tree Display
			Node* nodeDisplayName = treeDisplay->searchByName(st.getCarName());
			// Find the Personal key user-entered in tree Sound
			nodeDisplay = treeDisplay->searchByPersonalKey(st.getPersonalKey());

			// If the Owner name is exist but Personal key is not exist, then send warning message
			if (isKeyExisted(nodeDisplayName) && !isKeyExisted(nodeDisplay)) {

				// Display warning message
				cout << endl;
				cout << "-- WARNING: The Owner name have been existed, please enter another name!!! --" << endl;
				cout << endl;

				system("pause");
				existed = true;
			}

		} while (existed == true);

		// Initialize Display
		Display* dpl = new Display(st);

		// Find the node is store personal key that user input
		Node* nodeSound = treeSound->searchByPersonalKey(st.getPersonalKey());
		Node* nodeGeneral = treeGeneral->searchByPersonalKey(st.getPersonalKey());

		// The case user input personal key is exist
		if (isKeyExisted(nodeDisplay))
		{
			//Update setting
			nodeSound->data->updateSetting(st);
			nodeDisplay->data->updateSetting(st);
			nodeGeneral->data->updateSetting(st);

			cout << "-> This car already existed, data will be overriten" << endl;
			// Input data
			dpl->nhapThongTin(st);
			dynamic_cast<Display*>(nodeDisplay->data)->updateDisplay(st, dpl->get_light_level(), dpl->get_screen_light_level(), dpl->get_taplo_light_level());
		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			//Add new Display
			dpl->nhapThongTin(st);	//require user input data of Display
			treeDisplay->insert(dpl);

			//Add empty Sound and General
			treeSound->insert(new Sound(st));
			treeGeneral->insert(new General(st));
			displayCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << displayCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to handle menu print setting information
*/
void XuatThongTinCaiDat() {
	
	// Get type of sort that user chose
	int sortType = selectType();
	// Handle print data out according to the type user's choice
	XuatThongTinCaiDat(sortType);
}

/*
* The function to handle menu print setting information
*/
void XuatThongTinCaiDat(int sortType) {
	//declare local variables and string regex
	int selection;
	regex isDigit("^[1-5]");
	bool error = false;

	//Over and over again constantly until user choice Exit
	do {
		string user_choice;

		do {
			error = false;
			system("cls");

			user_choice = "";
			//display menu
			cout << " --- SELECT MENU --- " << endl;
			cout << " 1. Print display setting information" << endl;
			cout << " 2. Print sound setting information" << endl;
			cout << " 3. Print general setting information" << endl;
			cout << " 4. Print all setting information" << endl;
			cout << " 5. Exit" << endl;
			cout << " Your selection: ";
			cin >> user_choice;

			//catch the case user input is not a number and from 0 to 5
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Please enter a number from 0 to 5!" << endl;
				system("pause");
				error = true;
			}
		} while (error == true);

		selection = stoi(user_choice);		//cast string to int
		system("cls");

		//Handle the cases user choose
		switch (selection) {

		case 1:		//case 1: print data of Display
			XuatThongTinCaiDat_Display(sortType);
			system("pause");
			system("cls");
			break;

		case 2:		//case 2: print data of Sound
			XuatThongTinCaiDat_Sound(sortType);
			system("pause");
			system("cls");
			break;

		case 3:		//case 3: print data of General
			XuatThongTinCaiDat_General(sortType);
			system("pause");
			system("cls");
			break;

		case 4:		//case 4: print all data
			XuatThongTatCaTinCaiDat();
			system("pause");
			system("cls");
			break;

		case 5:		//case 5: Back main menu
			menu();
			break;
		}
	} while (selection != 5);
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c)
			buff += n;
		else if (n == c && buff != "")
		{
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);

	return v;
}

/*
* The function work with file data timezone and set timezone
*/
void downloadTimeZone() {
	//declare variables
	ifstream file_in;
	file_in.open("timezones.txt");
	CommonInfo commonInfo;
	string data;
	vector<string> data_vector;

	//read until end of file
	while (!file_in.eof()) {
		while (getline(file_in, data)) {
			// cut data
			data_vector = explode(data, '/');

			if (data_vector.size() == 2)
			{
				// set data of Timezone to common info vector
				commonInfo.setNumber(data_vector[0]);
				commonInfo.setName(data_vector[1]);
				timezoneList.push_back(commonInfo);
			}
		}
	}
	// close file after worked
	file_in.close();

	// Sort list Timezone
	sort(timezoneList.begin(), timezoneList.end(), comparatorTimezone);
}

/*
* The function work with file data language and set language
*/
void downloadLanguage() {

	//declare variables
	ifstream file_in;
	file_in.open("languages.txt");
	CommonInfo commonInfo;
	string data;
	vector<string> data_vector;

	//read until end of file
	while (!file_in.eof()) {
		while (getline(file_in, data)) {
			// cut data
			data_vector = explode(data, '/');

			if (data_vector.size() == 2)
			{
				// set data of Language to common info vector
				commonInfo.setNumber(data_vector[0]);
				commonInfo.setName(data_vector[1]);
				languageList.push_back(commonInfo);
			}
		}
	}
	// close file after worked
	file_in.close();

	//Sort list Language
	sort(languageList.begin(), languageList.end(), comparatorLanguage);
}

/*
* The function to show menu, user will select sort type (Owner name or Personal key) that user want to sort
*/
int selectType() {

	string user_choice;
	bool error = false;
	regex isNumber("^[0-3]");

	// Require user enter their choice which the type user want to search 
	do {
		error = false;
		system("cls");
		cout << "Please select a type that you want to sort by:" << endl;
		cout << "1. Owner name" << endl;
		cout << "2. Personal key" << endl;
		cout << "3. Back" << endl;
		cout << "Your selection: ";
		cin >> user_choice;

		// Check user-entered is from 1 to 3 or not
		if (!regex_match(user_choice, isNumber))
		{
			cout << "Please enter a number from 1 to 3!" << endl;
			system("pause");
			cin.ignore(256, '\n');
			error = true;
		}
	} while (error == true);
	// Cast user_choice to integer
	return stoi(user_choice);
}

/*
* The function to print data of Sound
*/
void XuatThongTinCaiDat_Sound(int sortType) {

	// Print out information of result
	system("cls");
	cout << "--- Sound Setting ---" << endl;
	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(10) << left << "Navi" << setw(10) << left << "Notify" << endl;

	// Handle case user choice
	switch (sortType)
	{
	case 1:		// The case sort by owner name 
	{
		// Get all data of Sound and srote to vector
		vector<Sound*>* listSound = new vector<Sound*>;
		listSound = treeSound->getAllSound(listSound);
		// Create a Set to store the list of General is sort by owner name
		set<Sound*, cmpSound> setSound(listSound->begin(), listSound->end());

		// Print Sound data out
		for (Sound* item : setSound) {
			item->xuatThongTin();
			cout << endl;
		}
		break;
	}
	case 2:		// The case sort by personal key 
	{
		// Use inorder traversal ro print data out
		treeSound->printTree(soundType);
		cout << endl;
		break;
	}
	case 3:
		break;
	}
}

/*
* The function to print data of General
*/
void XuatThongTinCaiDat_General(int sortType) {

	// Print out information of result
	system("cls");
	cout << "--- General Setting ---" << endl;
	cout << setw(20) << left << "Owner name" << setw(20) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(50) << left << "TimeZone" << setw(50) << left << "Language" << endl;

	// Handle case user choice
	switch (sortType)
	{
	case 1:		// The case sort by owner name 
	{
		// Get all data of General and srote to vector
		vector<General*>* listGeneral = new vector<General*>;
		listGeneral = treeGeneral->getAllGeneral(listGeneral);
		// Create a Set to store the list of General is sort by owner name
		set<General*, cmpGeneral> setGeneral(listGeneral->begin(), listGeneral->end());

		// Print General data out
		for (General* item : setGeneral) {
			item->xuatThongTin();
			cout << endl;
		}
		break;
	}
	case 2:		// The case sort by personal key 
	{
		// Use inorder traversal ro print data out
		treeGeneral->printTree(generalType);
		cout << endl;
		break;
	}
	case 3:
		break;
	}
}

/*
* The function to print data of Display
*/
void XuatThongTinCaiDat_Display(int sortType) {

	// Print out information of result
	system("cls");
	cout << "--- Display Setting ---" << endl;
	cout << setw(20) << left << "Owner name"
		<< setw(25) << left << "Email"
		<< setw(15) << left << "Key number"
		<< setw(15) << left << "ODO number"
		<< setw(20) << left << "Remind Service (km)"
		<< setw(15) << left << "Light level"
		<< setw(20) << left << "Screen light level"
		<< setw(15) << left << "Taplo level" << endl;

	// Handle case user choice
	switch (sortType)
	{
	case 1:		// The case sort by owner name 
	{
		// Get all data of Display and srote to vector
		vector<Display*>* listDisplay = new vector<Display*>;
		listDisplay = treeDisplay->getAllDisplay(listDisplay);
		// Create a Set to store the list of Display is sort by owner name
		set<Display*, cmpDisplay> setDisplay(listDisplay->begin(), listDisplay->end());

		// Print Display data out
		for (Display* item : setDisplay) {
			item->xuatThongTin();
			cout << endl;
		}
		break;
	}
	case 2:		// The case sort by personal key 
	{
		// Use inorder traversal ro print data out
		treeDisplay->printTree(displayType);
		cout << endl;
		break;
	}
	case 3:
		break;
	}
}

/*
* The function to print out result then user search data
*/
void printSearchResult(Node * resultDisplay, Node * resultSound, Node * resultGeneral)
{
	cout << "--- All Setting ---" << endl;
	// If one of result is Null, print out "NOT FOUND"
	if (resultDisplay == NULL || resultSound == NULL || resultGeneral == NULL) {
		cout << "NOT FOUND!!! \n" << endl;
	}
	else {	// If result is not NULL then cast result to correct type and print result out

		// Cast search result to corect type to print out
		Display* dpl_result = dynamic_cast<Display*>(resultDisplay->data);
		Sound* s_result = dynamic_cast<Sound*>(resultSound->data);
		General* g_result = dynamic_cast<General*>(resultGeneral->data);

		// get Timezone
		string timezoneStr = "";
		timezoneStr = getStringTimezone(g_result->get_timeZone());

		// Print out information of result
		cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << endl;
		//Print data of Setting
		cout << setw(20) << left << resultDisplay->data->getCarName()
			<< setw(25) << left << resultDisplay->data->getEmail()
			<< setw(20) << left << resultDisplay->data->getPersonalKey()
			<< setw(20) << left << resultDisplay->data->getODO()
			<< setw(20) << left << resultDisplay->data->getServiceRemind() << endl;

		//Print data of Display
		cout << setw(20) << left << "Display:" << setw(15) << "Light level" << setw(20) << "Screen Light level" << setw(15) << "Taplo Light" << endl;
		cout << setw(20) << left << ""
			<< setw(15) << dpl_result->get_light_level()
			<< setw(20) << dpl_result->get_screen_light_level()
			<< setw(15) << dpl_result->get_taplo_light_level() << endl;

		//Print data of Sound
		cout << setw(20) << left << "Sound:" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(15) << left << "Navigation" << setw(10) << left << "Notify" << endl;
		cout << setw(20) << left << ""
			<< setw(10) << s_result->get_media_level()
			<< setw(10) << s_result->get_call_level()
			<< setw(15) << s_result->get_navi_level()
			<< setw(10) << s_result->get_notification_level() << endl;

		//Print data of General
		cout << setw(20) << "General:" << setw(50) << "Timezone" << setw(50) << "Language" << endl;
		cout << setw(20) << left << ""
			<< setw(49) << timezoneStr
			<< setw(50) << g_result->get_language() << endl;
	}
}

/*
* The function to print all data
*/
void XuatThongTatCaTinCaiDat() {

	// declare variables
	int selection = 1;
	bool error = false;
	regex isNumber("^[0-3]");
	regex isPersonalKey("[0-9]+");
	string user_choice;

	// Require user enter their choice which the type user want to search 
	do {
		error = false;
		system("cls");
		cout << "Please select a type that you want to search by:" << endl;
		cout << "1. Owner name" << endl;
		cout << "2. Personal key" << endl;
		cout << "3. Back" << endl;
		cout << "Your selection: ";
		cin >> user_choice;

		// Check user-entered is from 1 to 3 or not
		if (!regex_match(user_choice, isNumber))
		{
			cout << "Please enter a number from 1 to 3!" << endl;
			system("pause");
			cin.ignore(256, '\n');
			error = true;
		}
	} while (error == true);
	// Cast user_choice to integer
	selection = stoi(user_choice);
	system("cls");

	// Handle case user choice
	switch (selection)
	{
	case 1:		// The case search by owner name 
	{
		// Require user enter owner name which one want to search 
		string name = "";
		cout << "Please enter the owner name: "; cin >> name;

		// Find the node in the trees (Display, Sound and General) by owner name that user-entered
		Node* resultDisplay = treeDisplay->searchByName(name);
		Node* resultSound = treeSound->searchByName(name);
		Node* resultGeneral = treeGeneral->searchByName(name);

		// Print out result
		printSearchResult(resultDisplay, resultSound, resultGeneral);
		break;
	}
	case 2:		// The case search by personal key 
	{
		string personalKey;

		// Require user enter personal key which one want to search 
		do {
			error = false;
			system("cls");
			personalKey = "";
			cout << "Please enter the personal key: "; cin >> personalKey;

			//Check key is numberic
			if (!regex_match(personalKey, isPersonalKey))
			{
				cout << "PERSONAL KEY must be a digit! \n" << endl;
				error = true;
				cin.ignore(256, '\n');
			}

			//Check key is 8 digitals
			if (personalKey.length() != 8)
			{
				cout << "PERSONAL KEY must have 8 digitals! \n" << endl;
				error = true;
				cin.ignore(256, '\n');
			}
		} while (error == true);
		
		// Find the node in the trees (Display, Sound and General) by personal key that user-entered
		Node* resultDisplay = treeDisplay->searchByPersonalKey(personalKey);
		Node* resultSound = treeSound->searchByPersonalKey(personalKey);
		Node* resultGeneral = treeGeneral->searchByPersonalKey(personalKey);

		// Print out result
		printSearchResult(resultDisplay, resultSound, resultGeneral);
		break;
	}
	case 3:
		break;
	}
}

/*
* The function to write data to file
*/
void writeDataToFile() {

	//declare file stream variables
	ofstream file_out;

	// get all value in setting array
	string formatString;

	// Handle open file and write data into file
	try
	{
		// open txt file
		file_out.open("Settings.txt");

		// Initialize vector to store data
		vector<Display*>* listDisplay = new vector<Display*>;
		vector<Sound*>* listSound = new vector<Sound*>;
		vector<General*>* listGeneral = new vector<General*>;

		// Get data of Display, Sound and General in tree
		listDisplay = treeDisplay->getAllDisplay(listDisplay);
		listSound = treeSound->getAllSound(listSound);
		listGeneral = treeGeneral->getAllGeneral(listGeneral);

		// Write data of Setting, Display, Sound and General to file
		for (int i = 0; i < listDisplay->size(); i++)
		{
			// Concatenate Setting data to a string
			formatString = "Setting:" + listDisplay->at(i)->formatTypeSetting() + "/";

			// Concatenate Display data to a string
			formatString += "Display:" + listDisplay->at(i)->formatTypeDisplay() + "/";

			// Concatenate Sound data to a string
			formatString += "Sound:" + listSound->at(i)->formatTypeSound() + "/";

			// Concatenate General data to a string 
			formatString += "General:" + listGeneral->at(i)->formatTypeGeneral() + "/";

			// Write data to file
			file_out << formatString + "\n";
		}

		// close file after worked
		file_out.close();
	}
	catch (...)		// Throw message when occur error during write file
	{
		cout << "Exception occur when save file!";
	}
}

// Get data from file setting.txt
void readDataFromFile() {

	//declare file stream variables
	ifstream file_in;
	string data;

	// Handle read data from file and add data to List
	try
	{
		// Open file setting.txt
		file_in.open("Settings.txt");

		// Check if file is open
		if (file_in.is_open())
		{
			// read each line in text file
			while (!file_in.eof())
			{
				// Get a line in file
				getline(file_in, data);
				// Use data have just get from file to handle add data to list
				handleDataInFile(data);
			}
		}
	}
	catch (...)		// Throw message when occur error during read file
	{
		cerr << "Exception occur when open file!" << endl;
	}
}

/*
* The function to handle separate string data file, check and add data from file to List
*/
void handleDataInFile(string line) {

	int currentSettingCount = 0;

	// Continue separate string in dataInLine and store in vector
	vector<string> data_in_line = explode(line, '/');
	// Declare temparory value for Setting data
	string car_name, email, personal_key, odo, service_remind;

	// Loop each data cluster in data_in_line
	for (int i = 0; i < data_in_line.size(); i++)
	{
		// Separate string in data_in_line and store in vector sub_data
		vector<string> sub_data = explode(data_in_line[i], ':');

		// The case is Setting
		if (sub_data[0] == "Setting")
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Assign data to temp variables
			car_name = dataDetail[0];
			email = dataDetail[1];
			personal_key = dataDetail[2];
			odo = dataDetail[3];
			service_remind = dataDetail[4];
		}
		else if (sub_data[0] == "Display")	// The case is Display
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to Display list
			// The order of the parameters passed: light level-[0], screen level-[1], taplo level-[1]
			Display* dpl = new Display(st);
			dpl->updateDisplay(st, stoi(dataDetail[0]), stoi(dataDetail[1]), stoi(dataDetail[2]));
			treeDisplay->insert(dpl);
			displayCount++;

		}
		else if (sub_data[0] == "Sound")	// The case is Sound
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to Sound list
			Sound* s = new Sound(st);
			s->updateSound(st, stoi(dataDetail[0]), stoi(dataDetail[1]), stoi(dataDetail[2]), stoi(dataDetail[3]));
			treeSound->insert(s);
			soundCount++;

		}
		else if (sub_data[0] == "General")	// The case is General
		{
			vector<string> dataDetail = explode(sub_data[1], ';');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to General list
			General* g = new General(st);
			g->updateGeneral(st, dataDetail[0], dataDetail[1]);
			treeGeneral->insert(g);
			generalCount++;
		}
	}
}

/*
* The function to check key user-entered is exist or not
*/
bool isKeyExisted(Node* node) {

	// Check that node is exist or not
	if (!node == NULL) {
		return true;
	}

	//if key is not exist
	return false;
}

/*
* The function to find and get string timezone
*/
string getStringTimezone(string timezone) {

	//Loop each item in timezone list to find and get timezone data match with passed parameter
	for (CommonInfo &item : timezoneList) {

		// If match, return a string = UTC / Area
		if (item.getName() == timezone) {
			return item.getNumber() + "/" + item.getName();
		}
	}

	// If is not match, return not Found
	return "Not Found!";
}

/*
* The function to sort list Timezone by UTC
*/
bool comparatorTimezone(CommonInfo c1, CommonInfo c2) {
	return (c1.getNumber() < c2.getNumber());
}

/*
* The function to sort list Language by alphabet
*/
bool comparatorLanguage(CommonInfo c1, CommonInfo c2) {
	return (c1.getName() < c2.getName());
}