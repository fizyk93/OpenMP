#include <omp.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <bitset> 

using namespace std;

const int size = 2000000;
bool *primes = NULL;

bitset<4473> primesSet;

void initializeVector(vector<bool> *primes, int n)
{
	for (int i = 0; i < n; i++)
	{
		primes->push_back(true);
	}

	cout << endl;
}

void initializeTable()
{
	if (primes == NULL)		primes = new bool[size];
	for (int i = 0; i < size; i++)
		primes[i] = true;
}

void initializePrimesSet()
{

	primesSet.set();

	for (int i = 2; i < (int)sqrt((double)primesSet.size()); i++)
	{
		if (!primesSet.test(i)) continue;

		for (int j = i * 2; j < primesSet.size(); j += i)
			primesSet.reset(j);
	}
}

void printPrimes(vector<bool> primes)
{
	int n = 0;
	for (vector<bool>::iterator it = primes.begin(); it != primes.end(); it++)
	{
		if (*it) cout << n << " ";
		n++;
	}
}

void printPrimes(bool *primes)
{
	for (int i = 0; i < size; i++)
	{
		if (primes[i]) cout << i << " ";
	}
}

void noOfPrimes()
{
	int counter = 0;
	for (int i = 0; i < size; i++)
	{

		if (primes[i])
		{
			counter++;
		}
	}

	cout << "counter: " << counter << endl;
}

void printResult(clock_t result)
{
	cout << "Wynik: " << ((double)result)/CLOCKS_PER_SEC << endl;
}

void divMethod()
{
	initializeTable();

	clock_t start, finish;
	start = clock();

	for (int i = 2; i < size; i++)
	{
		for (int j = 2; j <= sqrt((double)i); j++)
		{
			if (primes[j] && !(i%j))
			{
				//cout << "primes[" << j << "] == true && !(" << i << "%" << j << ")" << endl;
				primes[i] = false;
				break;
			}
		}
	}

	finish = clock();
	printResult(finish - start);
	//printPrimes(primes);
	
}

void divMethodAlt()
{
	initializeTable();

	clock_t start, finish;
	start = clock();

	for (int i = 2; i < size; i++)
	{
		for (int j = 2; j <= sqrt((double)i); j++)
		{
			if (primesSet.test(j) && !(i%j))
			{
				//cout << "primes[" << j << "] == true && !(" << i << "%" << j << ")" << endl;
				primes[i] = false;
				break;
			}
		}
	}
	

	finish = clock();
	printResult(finish - start);
	//printPrimes(primes);

}

void sieveMethod()
{
	/*vector<bool> primes;
	
	initializeVector(&primes, size);*/

	initializeTable();

	clock_t start, finish;
	start = clock();
	for (int i = 2; i < (int)sqrt((double)size); i++)
	{
		if (!primes[i]) continue;

		for (int j = i * 2; j < size; j += i)
			primes[j] = false;
	}
	finish = clock();

	printResult(finish - start);
	//printPrimes(primes);
}

void sieveMethodAlt()
{
	initializeTable();

	clock_t start, finish;
	start = clock();

	int maxIter = (int)((double)size / 120000);

	for (int x = 0; x <= maxIter; x++)
	{
		int min = x * 120000;
		min = (min < 2)?2:min;
		int max = min + 120000;
		max = (max > size) ? size : max;

		for (int i = 2; i < (int)sqrt((double)size); i++)
		{
			if (!primesSet.test(i)) continue;
			int minIter = min - min%i;
			minIter = (minIter <= i) ? (2 * i) : minIter;
			for (int j = minIter; j < max; j += i)
				primes[j] = false;
		}
	}
	finish = clock();

	printResult(finish - start);
	//printPrimes(primes);
}

void divMethodPar()
{
	/*vector<bool> primes;
	
	initializeVector(&primes, size);*/

	initializeTable();
	
	clock_t start, finish;
	start = clock();

#pragma omp parallel for schedule(dynamic, 1)
	for (int i = 2; i < size; i++)
	{
		for (int j = 2; j <= sqrt((double)i); j++)
		{
			if (primes[j] && !(i%j))
			{
				primes[i] = false;
				break;
			}
		}
	}

	finish = clock();

	printResult(finish - start);
	//printPrimes(primes);

}

void divMethodAltPar()
{
	initializeTable();

	clock_t start, finish;
	start = clock();

#pragma omp parallel for schedule(dynamic, 1)
	for (int i = 2; i < size; i++)
	{
		for (int j = 2; j <= sqrt((double)i); j++)
		{
			if (primesSet.test(j) && !(i%j))
			{
				//cout << "primes[" << j << "] == true && !(" << i << "%" << j << ")" << endl;
				primes[i] = false;
				break;
			}
		}
	}


	finish = clock();
	printResult(finish - start);
	//printPrimes(primes);

}


void sieveMethodPar()
{
	/*vector<bool> primes;
	
	initializeVector(&primes, size);*/

	initializeTable();

	clock_t start, finish;
	start = clock();

#pragma omp parallel for schedule(dynamic, 1)
	for (int i = 2; i < (int)sqrt((double)size); i++)
	{
		if (!primes[i]) continue;

		for (int j = i * 2; j < size; j += i)
			primes[j] = false;
	}

	finish = clock();

	printResult(finish - start);
	//printPrimes(primes);
}

void sieveMethodAltPar()
{
	initializeTable();

	clock_t start, finish;
	start = clock();

	int maxIter = (int)((double)size / 120000);

	for (int x = 0; x <= maxIter; x++)
	{
		int min = x * 120000;
		min = (min < 2) ? 2 : min;
		int max = min + 120000;
		max = (max > size) ? size : max;

#pragma omp parallel for schedule(dynamic, 1)
		for (int i = 2; i < (int)sqrt((double)size); i++)
		{
			if (!primesSet.test(i)) continue;
			int minIter = min - min%i;
			minIter = (minIter <= i) ? (2 * i) : minIter;
			for (int j = minIter; j < max; j += i)
				primes[j] = false;
		}
	}
	finish = clock();

	printResult(finish - start);
	//printPrimes(primes);
}

int main()
{

	omp_set_num_threads(omp_get_max_threads());
	initializePrimesSet();

	//divMethod();
	
	//sieveMethodAlt();
	//noOfPrimes();
	//sieveMethod();
	//noOfPrimes();
	//sieveMethodAltPar();
	//noOfPrimes();
	divMethod();
	noOfPrimes();
	divMethodAlt();
	noOfPrimes();
	divMethodPar();
	noOfPrimes();
	divMethodAltPar();
	noOfPrimes();
	
	
	
	
	delete[] primes;

	getchar();
	return 0;
}