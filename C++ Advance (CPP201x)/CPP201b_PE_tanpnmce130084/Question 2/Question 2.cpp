#include <iostream>
#include <string>
#include "maxTemplate.cpp"

using namespace std;

int main()
{
	// --- Use template maxTemplate ---
	// Use template on int type
	int i_one = 3, i_two = 5;
	cout << "The max of " << i_one << " and " << i_two << " is " << myMax(i_one, i_two) << endl;

	
	// Use template on float type
	float f_one = 5.6, f_two = 7.3;
	cout << "The max of " << f_one << " and " << f_two << " is " << myMax(f_one, f_two) << endl;

	// Use template on string type
	string str_one = "donkey", str_two = "apple";
	cout << "The max of " << str_one << " and " << str_two << " is " << myMax(str_one, str_two) << endl;

	return 0;
}