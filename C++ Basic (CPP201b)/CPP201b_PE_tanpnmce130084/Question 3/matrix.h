#ifndef matrix_H_
#define matrix_H__H_

const int MAXROWS = 2;
const int MAXCOLS = 3;

template <class T>
class Matrix
{
public:

	// Constructor
	Matrix();	// Set rows to MAXROWS and cols to MAXCOLS
				// Initialize all the values of doubleArray to zero

	// Getter functions
	void printMatrix();

	// Setter functions
	void setMatrix(T[][MAXCOLS]);	// set the doubleArray to what is sent
	void addMatrix(T[][MAXCOLS]);	// add an array to doubleArray
	void addMatrix(Matrix anotherMatrix);

	//No destructor needed

private:
	T doubleArray[MAXROWS][MAXCOLS];
	int rows;
	int cols;
};


#endif /* matrix_H__H_ */