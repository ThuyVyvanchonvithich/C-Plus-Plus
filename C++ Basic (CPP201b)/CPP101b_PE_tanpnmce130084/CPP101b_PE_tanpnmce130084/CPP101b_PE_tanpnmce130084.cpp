#include <iostream>
using namespace std;

int calculateFn(int);
int calculatePn(int);

int main()
{
	int n = 0;

	cout << "Enter n: ";
	cin >> n;

	cout << endl;

	//result of F(n)
	cout << "F(n) = " << calculateFn(n) << endl;
	cout << endl;
	cout << "P(n) = " << calculatePn(n) << endl;

}

int calculateFn(int n) {
	int result = 1;
	for (int i = n; i > 0; i--) {
		result *= i;
	}

	return 3 * result;
}

int calculatePn(int n) {
	int result = 1;
	for (int i = 0; i <= n; i++) {
		//result = (2 * i) * (2 * i + 2);
		result *= (2 * i + 2);
	}

	return result;
}
