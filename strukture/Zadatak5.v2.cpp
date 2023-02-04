// Zadatak 4.5
/* 2D niz na slici predstavlja šahovsku tablu. 
Napraviti i testirati u main programu slijedeće funkcije:

Funkcija za unos elemenata tako da se u svako crno polje 
unese parni broj sa neparnim brojem cifara a u svako bijelo polje 
unese neparni broj sa parnim brojem cifara.

Funkcija koja će računati aritmetičku sredinu svih brojeva na 
crnim poljima iznad glavne dijagonale.*/

#include<iostream>
#include<windows.h>
#include<cstdlib>

void unos(int**, int);
void ispis(int**, int);
float aritmetickaSredina(int**, int);

int main() {
	srand(time(NULL));
	const int size = 8;
	int** niz = new int* [size];
	for (int i = 0; i < size; i++)
		*(niz + i) = new int[size];

	unos(niz, size);
	ispis(niz, size);
	std::cout << "\n\n\nProsjek iznad glavne dijagonale na crnim poljima je: "; 
	std::cout << aritmetickaSredina(niz, size);

	for (int i = 0; i < size; i++)
		delete[] * (niz + i);
	delete[] niz; niz = nullptr;

	system("pause>nul");
	return 1;
}

void unos(int** niz, int size) {

	int x; std::cout << "1 za manuelni unos, za automatski bilo koji drugi broj: "; std::cin >> x;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int broj; int brojCifara;
			do {
				if (x == 1) {
					std::cout << "[" << i << "][" << j << "]: "; std::cin >> broj;
				}
				else broj = rand() % 1000000 + 1;

				brojCifara = log10(broj) + 1;

			} while ((!((i + j) % 2 != 0) && (brojCifara % 2 == 0 || broj % 2 != 0)) || 
				(!((i + j) % 2 == 0) && (brojCifara % 2 != 0 || broj % 2 == 0)));
			*(*(niz + i) + j) = broj;
		}
	}

}
void ispis(int** niz, int size) {

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			HANDLE hConsole;
			int k = 0;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if ((i + j) % 2 == 0) k = 7;
			else k = 14;

			SetConsoleTextAttribute(hConsole, k);
			std::cout << *(*(niz + i) + j) << "|\t";
		}
		std::cout << "\n";
	}
}

float aritmetickaSredina(int** niz, int size) {

	float arsr = 0.0f;
	int brojac = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j += 2)
		{
			arsr += *(*(niz + i) + j); brojac++;
		}
	}

	return (arsr / float(brojac));
}