/*Kreirati dvodimenzionalni dinamicki niz ciji su elementi objekti tipa
figura (figura je struktura cija su obiljezja data u nastavku). Omoguciti
korisniku da unese dimenzije niza te omoguciti unos elemenata na nacin da se
na svako crno polje unese figura cija je visina veca od 5cm a na svako bijelo
polje figura cija je visina manja od 5cm. Ukoliko je unesena visina jednaka
5cm, polje treba ostati prazno.

struct figura{
	int ID;
	char* NazivFigure;
	float* VisinaFigure;
};

Potrebno je napraviti funkciju koja ce racunati prosjecnu visinu svih figura
koje se nalaze na crnim poljima iznad sporedne dijagonale. Funkcija treba
vratiti pokazivac na memorijsku lokaciju u kojoj je upisana ta vrijednost.
U ovom zadatku obavezno je koristiti aritmetiku pokazivaca
*/
#include<iostream>
#include <windows.h>

struct Figura {
	int _ID = 0;
	char* _NazivFigure;
	float* _VisinaFigure;

	Figura() {
		_ID = 0;
		_NazivFigure = nullptr;
		_VisinaFigure = nullptr;
	}

	void set(const char* naziv, float visina, int ID) {
		delete[] _NazivFigure;
		_NazivFigure = alokacijaTexta(naziv);
		_VisinaFigure = new float(visina);
		_ID = ID;
	}

	char* alokacijaTexta(const char* izvor) {
		if (izvor == nullptr) return nullptr;

		int velicina = strlen(izvor) + 1;
		char* destinacija = new char[velicina];
		strcpy_s(destinacija, velicina, izvor);

		return destinacija;
	}

	char* unosTexta() {
		char text[500];
		std::cin.getline(text, 500);
		return alokacijaTexta(text);
	}

	float getVisina() { return *_VisinaFigure; }

	void print() {
		std::cout << _ID << " - " << *_NazivFigure << " - " << *_VisinaFigure << "cm\n";
	}

	void print2(int flag) {
		HANDLE  hConsole;
		int k = 0;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (flag == 0)
			k = 14;
		else if (flag == 1)
			k = 7;
		else if (flag == 2)
			k = 4;

		SetConsoleTextAttribute(hConsole, k);
		std::cout << *_VisinaFigure << "|";
	}

	~Figura() {
		delete[] _NazivFigure;
		delete _VisinaFigure;
	}
};

void test1();

float* prosjek(Figura**& f, int redovi, int kolone) {
	float prosjek = 0.0f;
	int brojac = 0;

	for (int i = 0; i < redovi; i++)
	{
		for (int j = 0; j < kolone; j++)
		{
			if (((i + j) < redovi) && ((i + j) % 2 != 0)) {
				prosjek += (*(f + i) + j)->getVisina(); brojac++;
			}
		}
	}
	prosjek /= float(brojac);
	return &prosjek;
}

int main() {

	test1();

	system("pause>nul");
	return 1;
}

void test1() {

	int red; int kolona;

	std::cout << "Unesite redove: "; std::cin >> red;
	std::cout << "Unesite kolone: "; std::cin >> kolona;
	std::cout << "\n\n\n\n***********************************************************\n";

	Figura** f = new Figura * [red];

	for (int i = 0; i < red; i++)
		*(f + i) = new Figura[kolona];

	{
		int ID = 0;
		for (int i = 0; i < red; i++)
		{
			for (int j = 0; j < kolona; j++)
			{
				float visina = 0;
				if ((i + j) % 2 == 0) visina = (rand() % 4) + 1;
				else { visina += 5; visina += (rand() % 5) + 1; }

				(*(f + i) + j)->set("figura", visina, ID + 1); ID++;
			}
		}
	}

	for (int i = 0; i < red; i++)
	{
		for (int j = 0; j < kolona; j++)
		{
			int k = 0;
			if ((i + j) % 2 != 0) k = 1;
			(*(f + i) + j)->print2(k); std::cout << "\t";
		}
		std::cout << "\n-----------------------------------------------------------\n";
	}

	std::cout << "\n\n\n\n\n";
	float p = *prosjek(f, red, kolona);
	std::cout << "Prosjek: " << p;

	std::cout << "\n\n\n\n\n";

	for (int i = 0; i < red; i++)
	{
		for (int j = 0; j < kolona; j++)
		{
			int k = 0;
			if ((i + j) % 2 != 0) k = 1;
			if (((i + j) < red) && ((i + j) % 2 != 0)) k = 2;
			(*(f + i) + j)->print2(k); std::cout << "\t";
		}
		std::cout << "\n-----------------------------------------------------------\n";
	}

	for (int i = 0; i < red; i++)
		delete[] * (f + i);
	delete[] f; f = nullptr;

	system("pause>nul");
}