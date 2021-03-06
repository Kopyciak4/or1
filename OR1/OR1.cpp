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

int count(int from, int to, int c) { 
	int licznik = 0;
	for (int j = from; j <= to; j++) {
		if (f(j) == c) { 
			licznik++;
		}
	}
	return licznik;
}

int main(int argc, char *argv[]) // nazwa programu + liczba parametrow, tablica [nazwaProgramu, parametr1, parametr2....
{
	int c;
	try {
		if (argc < 2)
			throw 'err';

		
		istringstream ss(argv[1]);
		if (!(ss >> c)) {

			throw 'err';
		}
		else if (!ss.eof()) {
			throw "zla liczba";
		}
	}
	catch (string h) {
		cout << "zjebales";
		return 1;
	}
	
	int result = 0;

	MPI_Init(&argc, &argv);
	int size;
	int rank;

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int range = 2000000000 / size;
	int missingRange = 2000000000 % size;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		
		for (int k = 1; k < size; k++) { 
			int partialCounter;
			MPI_Recv(&partialCounter,1,MPI_INT,k,1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // wynik zadania, liczba wynikow, typ danych, nr procesu ktory ma otrzymac, tag, obiekt comm_world, status 
			result += partialCounter;
		}
		cout << count(1, range, c) + result;

	}
	else {
		int partialCounter = count(rank * range + 1, range * (rank + 1) + ((rank + 1 == size) ? missingRange: 0), c); // ? : !void
	
		MPI_Send(&partialCounter, 1, MPI_INT, 0,1, MPI_COMM_WORLD); 
	}

	MPI_Finalize();	
	
} 
