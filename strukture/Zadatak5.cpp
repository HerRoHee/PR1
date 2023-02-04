/*2D niz na slici predstavlja šahovsku tablu. 
Napraviti i testirati u main programu slijedeće funkcije:

Funkcija za unos elemenata tako da se u svako crno polje 
unese parni broj sa neparnim brojem cifara a u svako bijelo 
polje unese neparni broj sa parnim brojem cifara.
Funkcija koja će računati aritmetičku sredinu svih brojeva 
na crnim poljima iznad glavne dijagonale. Za olaksanje rjesenja, 
mozete izabrati prototip funkcija po zelji te kreirati dodatne funkcije po potrebi.*/

#include<iostream>
#include<cstdlib>
#include <windows.h>

char* enterText() {
	char temp[500]; std::cin.ignore();
	std::cout << "Enter text: \n";  std::cin.getline(temp, 500);

	int size = strlen(temp) + 1;
	char* text = new char[size];
	strcpy_s(text, size, temp);

	return text;
}

struct Figura {

	int* _broj{ nullptr };

	Figura() {
		_broj = nullptr;
	}
	Figura(int broj) {
		if (_broj == nullptr) _broj = new int;
		*_broj = broj;
	}

	void set(int broj) {
		if (_broj == nullptr) _broj = new int;
		*_broj = broj;
	}

	void print(int flag) {
		HANDLE  hConsole;
		int k = 0;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (flag == 0) // Bijela polja
			k = 14;
		else if (flag == 1) // Crna polja
			k = 5;
		else if (flag == 2) // Select
			k = 4;

		SetConsoleTextAttribute(hConsole, k);
		std::cout << *_broj << "|\t";
	}

	~Figura() {
		delete _broj; _broj = nullptr;
	}

};

void aritmetickaSredina(Figura** f, int size) {
	float arsr = 0.00f;
	int brojac = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 1 + i; j < size; j += 2)
			// j = 0 + i, optimizacija, kada u novi red predje 
			// da mu je pocetna tacka od glavne dijagonale
		{
			
				arsr += *(*(f + i) + j)->_broj;
				brojac++;
			
		}
	}

	std::cout << "\n\n\n\nAritmeticka sredina: " << arsr / float(brojac) << "\n\n";

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i + j) % 2 != 0 && (i <= j)) { (*(f + i) + j)->print(2); }
			else if ((i + j) % 2 == 0) { (*(f + i) + j)->print(0); }
			else { (*(f + i) + j)->print(1); }

		}
		std::cout << "\n";
	}

}

int main() {

	srand(time(NULL));

	int size = 8;
	Figura** f = new Figura * [size];

	for (int i = 0; i < size; i++)
		*(f + i) = new Figura[size];

	int x;
	std::cout << "Za manuelni unos, unesite 1, inace upisite bilo koji drugi broj: "; std::cin >> x;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int broj;
			int brojCifara;

			if (x == 1)
			{
				do {
					std::cout << "[" << i << "][" << j << "]:";
					std::cin >> broj;
					brojCifara = log10(broj) + 1;
				} while (!(((broj % 2 == 0) && (brojCifara % 2 != 0) && ((i + j) % 2 != 0)) ||
					((broj % 2 != 0) && (brojCifara % 2 == 0) && ((i + j) % 2 == 0))));
			}
			else {
				do {
					broj = rand();
					brojCifara = log10(broj) + 1;
				} while (!(((broj % 2 == 0) && (brojCifara % 2 != 0) && ((i + j) % 2 != 0)) ||
					((broj % 2 != 0) && (brojCifara % 2 == 0) && ((i + j) % 2 == 0))));
			}
			(*(f + i) + j)->set(broj);
		}
	}

	std::cout << "\n\n_______________________________________\n";

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i + j) % 2 == 0) { (*(f + i) + j)->print(0); }
			else { (*(f + i) + j)->print(1); }
		}
		std::cout << "\n";
	}

	aritmetickaSredina(f, size);

	for (int i = 0; i < size; i++)
		delete[] * (f + i);

	delete[] f;

	system("pause>nul");
	return 1;
}