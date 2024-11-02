#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
static bool isUniqueElement(T* array, int aSize, T elem) {
	bool valid = true;
	for (int i = 0; i < aSize; i++) {
		if (array[i] == elem) {
			valid = false;
			break;
		}
	}
	return valid;
}

template <typename T>
static void push(T* &array, int &aSize, T elem) {
	T* temp = new T[aSize + 1];
	
	copy(array, array + aSize, temp);
	if (aSize != 0) { delete [] array; }
	
	temp[aSize] = elem;
	array = temp;
	aSize = aSize + 1;
}

// Array must not be empty
template <typename T>
static T pop(T* &array, int &aSize) {
	T toReturn = array[aSize - 1];
	T* temp = new T[aSize - 1];
	
	for (int i = 0; i < aSize - 1;  i++) { temp[i] = array[i]; }
	if (aSize == 0) { cout << "Error! Array size must not be 0 in order to be popped!" << endl; }
	if (aSize != 0) { delete [] array; }
	array = temp;
	aSize = aSize - 1;
	
	return toReturn;
}

template <typename T>
static string arrayToString(T* array, int aSize) {
	string s = "";
	s.append("[");
	for (int i = 0; i < aSize; i++) {
		if (i != 0) {
			s.append(", ");
		}
		s.append(array[i]);
	}
	s.append("]");
	
	return s;
}