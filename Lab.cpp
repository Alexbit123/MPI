#include <iostream>
#include <string>
#include "mpi.h"

using namespace std;

const int root = 0;

char s1, s2;

int main()
{
	string str, rbuf;
	int rank, commSize, step;
	MPI_Init(NULL, NULL);//инициализация парааллельной части
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);//определение номера процесса в группе
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);//определение общего числа параллельных процессoв size в группе
	MPI_Status status;

	if (rank == root)
	{
		cout << "Vvedite stroky: ";
		cin >> str;

		cout << "Cimvol zameny: ";
		cin >> s1;

		cout << "Na cho menyat: ";
		cin >> s2;

	}
	int p = (int)rank;
	step = str.size() / commSize;
	p = (p * step);

	MPI_Scatter(&str, str.size(), MPI_CHAR, &rbuf, str.size(), MPI_CHAR, 0, MPI_COMM_WORLD);
	
	
	for (int i = p; i < p + step; i++)
	{
		cout << "Rank: " << rank << endl;
		if (rbuf[i] == s1)
		{
			rbuf[i] = s2;
		}
		
	}
	

	if (rank == 0)
	{
		MPI_Gather(&rbuf, str.size(), MPI_CHAR, &str, str.size(), MPI_CHAR, 0, MPI_COMM_WORLD);
	}

	if (rank == root)
	{
		cout << str << endl;
	}


	MPI_Finalize();
	return 0;
}
