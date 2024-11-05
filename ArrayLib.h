#ifndef ARRAYLIB_H
#define ARRAYLIB_H

#include <algorithm>
#include <iostream>
#include <random>

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
	if (aSize == 0) { cout << "Error! Array size must not be 0 in order to be popped!" << endl; }
	
	T toReturn = array[aSize - 1];
	T* temp = new T[aSize - 1];
	
	for (int i = 0; i < aSize - 1;  i++) { temp[i] = array[i]; }
	if (aSize != 0) { delete [] array; }
	array = temp;
	aSize = aSize - 1;
	
	return toReturn;
}

template <typename T>
static void insert(T* &array, int &aSize, int index, T elem) {
	if (0 > index || index > aSize) {
		cout << "Error! Cannot insert element" << endl;
		cout << "Index " << index << " is out of range of array of size " << aSize << "!" << endl;
		return;
	}
	
	if (index == aSize) {
		push(array, aSize, elem);
		return;
	}
	
	T* temp = new T[aSize + 1];
	int aIndex = 0;
	for (int i = 0; i < aSize + 1; i++) {
		if (i == index) {
			temp[i] = elem;
			continue;
		}
		temp[i] = array[aIndex];
		aIndex++;
	}
	array = temp;
	aSize = aSize + 1;
}

// Array must not be empty
template <typename T>
static T remove(T* &array, int &aSize, int index) {
	if (0 > index || index >= aSize) {
		cout << "Error! Cannot remove element." << endl;
		cout <<	"Index " << index << " is out of range of array of size " << aSize << "!" << endl;
		return T();
	}
	
	if (index == aSize - 1) {
		return pop(array, aSize);
	}
	
	T toReturn = array[aSize - 1];
	
	T* temp = new T[aSize - 1];
	int tIndex = 0;
	for (int i = 0; i < aSize; i++) {
		if (i == index) { continue; }
		temp[tIndex] = array[i];
		tIndex++;
	}
	array = temp;
	aSize = aSize - 1;
	
	return toReturn;
}

// Move an element from index1 to index2
// - All other elements remain in the same order.
// - Every element from index1 to index2 are "shifted" over.
template <typename T>
static void shift(T* &array, int aSize, int index1, int index2) {
	if (index1 < 0 || index1 >= aSize) {
		cout << "Error! Cannot shift element." << endl;
		cout <<	"Index " << index1 << " is out of range of array of size " << aSize << "!" << endl;
	}
	
	if (index2 < 0 || index2 >= aSize) {
		cout << "Error! Cannot shift element." << endl;
		cout <<	"Index " << index2 << " is out of range of array of size " << aSize << "!" << endl;
	}
	
	T toShift = array[index1];
	T* temp = new T[aSize];
	int aIndex = 0;
	
	for (int i = 0; i < aSize; i++) {
		if (i == index1) {
			if (index1 < index2) {
				temp[i] = array[++aIndex];
			} else {
				temp[i] = array[aIndex++];
			}
		}
		if (i == index2) {
			temp[i] = toShift;
			aIndex--;
		}
		if (i != index1 && i != index2) {
			temp[i] = array[aIndex];
		}
		aIndex++;
	}
	
	array = temp;
}

template <typename T>
static void swap(T* &array, int aSize, int index1, int index2) {
	if (index1 < 0 || index1 >= aSize) {
		cout << "Error! Cannot swap element." << endl;
		cout <<	"Index " << index1 << " is out of range of array of size " << aSize << "!" << endl;
	}
	
	if (index2 < 0 || index2 >= aSize) {
		cout << "Error! Cannot swap element." << endl;
		cout <<	"Index " << index2 << " is out of range of array of size " << aSize << "!" << endl;
	}
	
	T dummy = array[index1];
	array[index1] = array[index2];
	array[index2] = dummy;
}

template <typename T>
static void shuffle(T* &array, int &aSize) {
	random_device dev;
	mt19937 rng(dev());
	
	T* temp = new T[aSize];
	int randomNum;
	for (int i = 0; i < aSize; i++) {
		uniform_int_distribution<mt19937::result_type> dist(0, aSize - (i + 1));
		randomNum = dist(rng);
		temp[i] = array[randomNum];
	}
	
	if (aSize > 0) { delete [] array; }
	array = temp;
}

template <typename T>
static T* copy(T* array, int aSize) {
	T* copy = new T[aSize];
	for (int i = 0; i < aSize; i++) {
		copy[i] = T(array[i]);
	}
	return copy;
}

static string arrayToString(string* array, int aSize) {
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

#endif