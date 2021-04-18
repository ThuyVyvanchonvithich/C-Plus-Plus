#include <iostream>
#include <math.h>

using namespace std;

/*
* The base class Cylinder
*/
class Cylinder {
protected:
	const float PI = 3.14;

public:
	Cylinder();
	void set_volume(int radius, int height);
};

Cylinder::Cylinder() {}
void Cylinder::set_volume(int radius, int height) {
	float volume = PI * (pow(radius, 2)) * height;
	cout << "Cylinder volume is: " << volume << endl;
}

/*
* The derived class Cone
*/
class Cone : public Cylinder {
public:
	Cone();
	void set_volume(int radius, int height);
};

Cone::Cone() {}
void Cone::set_volume(int radius, int height) {
	float volume = ( (float) 1 / 3) * PI * (pow(radius, 2)) * height;
	cout << "Cone volume is: " << volume << endl;
}

// Main function
int main()
{
	//Create instances of the base and derived class
	Cylinder cylinder;
	Cone cone;

	//Set the volume of the cylinder
	cylinder.set_volume(3, 4);
	//Set the volume of the cone
	cone.set_volume(3, 4);
}