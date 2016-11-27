//============================================================================
// Name        : temp.cpp
// Author      : Anderson Paschoalon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <malloc.h>
using namespace std;

template<typename T> T mode(list<T>* theList);
template<typename T>
void quickSort(T* vet, int left, int right);

int main()
{

	list<double> a;
	a.push_back(11.1);
	a.push_back(1.2);
	a.push_back(10);
	a.push_back(11);
	a.push_back(11);
	a.push_back(1.1);
	a.push_back(2);
	a.push_back(11);
	a.push_back(5);
	a.push_back(9.5);
	a.push_back(11);
	a.push_back(12);
	a.push_back(11);
	a.push_back(11);
	a.push_back(12);
	a.push_back(11.3);
	a.push_back(1.4);

	cout << "mode = " << mode(&a) << endl;

	return 0;
}

template<typename T>
void quickSort(T* vet, int left, int right)
{
	int p = left;
	int i = 0;
	T ch = 0;
	int j = 0;

	for (i = left + 1; i <= right; i++)
	{
		j = i;
		if (vet[j] < vet[p])
		{
			ch = vet[j];
			while (j > p)
			{
				vet[j] = vet[j - 1];
				j--;
			}
			vet[j] = ch;
			p++;
		}
	}
	if (p - 1 >= left)
		quickSort(vet, left, p - 1);
	if (p + 1 <= right)
		quickSort(vet, p + 1, right);
}

template<typename T>
T mode(list<T>* theList)
{
	T* vet;
	int listSize = theList->size();
	int i = 0;
	T candidate = 0;
	T prev = 0;
	int counter = 0;
	int largerCounter = 0;
	T mode = 0;
	vet = new T[listSize];

	if (listSize == 0)
	{
		return (0);
	}

	i = 0;

	for (typename list<T>::iterator it = theList->begin(); it != theList->end();
			it++)
	{
		vet[i] = *it;
		i++;
	}

	quickSort(vet, 0, listSize - 1);

	prev = vet[0];
	for (i = 0; i < listSize; i++)
	{
		candidate = vet[i];
		if (candidate == prev)
		{
			counter++;
			if (counter > largerCounter)
			{
				largerCounter = counter;
				mode = vet[i];
			}
		}
		else
			counter = 0;

		prev = vet[i];
	}

	delete[] vet;

	return (mode);
}



