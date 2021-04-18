#include <iostream>
using namespace std;

class Student {
public:
	char roll[8] = "";
	char name[30] = "";
	float point;

	Student() {
		cout << "Constructor of Student class" << endl;
		std::copy("", "", this->roll);
		std::copy("", "", this->name);
		this->point = 0;
	}

	Student(char roll[8], char name[30]) {
		std::copy(roll, roll + 8, this->roll);
		std::copy(name, name + 30, this->name);
		this->point = 0;
	}

	void display() {
		if (!(name == "" && roll == "")) {
			cout << "Rollnumber: " << this->roll << endl;
			cout << "Name: " << this->name << endl;
		}
		cout << "Mark: " << this->point << endl;
	}
};

int main()
{
	cout << "Run without error : 0.5 point" << endl << endl;
	cout << "TEST CASE 1 (1 point)" << endl;
	cin.ignore(255, '\n');
	Student student1;
	student1.display();
	cout << endl;

	cout << "Enter rollnumber: ";
	char roll[8];
	cin >> roll;
	cout << "Enter name: ";
	char name[30];
	cin.getline(name, cin.gcount());

	cout << endl << "TEST CASE 2 (1 point)" << endl;
	Student student2 = Student(roll, name);
	student2.display();
	cout << endl;
}