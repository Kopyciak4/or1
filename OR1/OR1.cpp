// OR1.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include "mpi.h" 
#include <sstream>
#include <iostream>

using namespace std;

int f(int i) {
	int i4_huge = 2147483647;
	int j, k, value = i;
	for (j = 1; j <= 5; j++) {
		k = value / 127773;
		value = 16807 * (value - k * 127773) - k * 2836;
		if (value <= 0)
			value = value + i4_huge;
	}
	return value;
}

int main(int argc, char *argv[])
{
	int c;
	istringstream ss(argv[1]);
	if (!(ss >> c)) {
		throw 'err';  
	}
	else if(!ss.eof()) {
		throw "zla liczba"; 
	}
	
	int licznik = 0;
	for (int j = 1; j <= 2000000000; j++) {
		if (f(j) == c) {
			licznik++;
		}
	}
	cout << licznik;
}